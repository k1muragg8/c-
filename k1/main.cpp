#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <hiredis/hiredis.h>
#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

boost::mutex mutex;

void processRedisQueue(const std::string& redisHost, int redisPort, const std::string& mysqlHost, const std::string& mysqlUser, const std::string& mysqlPassword, const std::string& mysqlDatabase) {
    // Redis 连接
    redisContext* redisContext = redisConnect(redisHost.c_str(), redisPort);
    if (redisContext == nullptr || redisContext->err) {
        std::cerr << "Error connecting to Redis: " << (redisContext ? redisContext->errstr : "unknown") << std::endl;
        return;
    }

    // MySQL 连接
    sql::Driver* driver = sql::mysql::get_driver_instance();
    std::unique_ptr<sql::Connection> connection(driver->connect(mysqlHost, mysqlUser, mysqlPassword));
    connection->setSchema(mysqlDatabase);

    while (true) {
        // 从 Redis 队列获取任务
        redisReply* reply = redisCommand(redisContext, "BLPOP my_queue 0"); // 使用 BLPOP 进行阻塞式弹出
        if (reply == nullptr || reply->type != REDIS_REPLY_ARRAY || reply->elements != 2) {
            std::cerr << "Error getting task from Redis" << std::endl;
            if (reply != nullptr) {
                freeReplyObject(reply);
            }
            continue;
        }

        std::string task = reply->element[1]->str;
        freeReplyObject(reply);

        // 处理任务（示例：将任务字符串转换为大写）
        std::string result = task;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);

        // 写入 MySQL
        try {
            std::unique_ptr<sql::Statement> statement(connection->createStatement());
            {
                boost::unique_lock<boost::mutex> lock(mutex);
                statement->execute("INSERT INTO my_table (data) VALUES ('" + result + "')");
            }
        } catch (sql::SQLException& e) {
            std::cerr << "Error writing to MySQL: " << e.what() << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 添加延迟，避免过度占用 CPU
    }

    redisFree(redisContext);
}

int main() {
    int numThreads = 4;
    std::vector<boost::thread> threads;

    std::string redisHost = "127.0.0.1";
    int redisPort = 6379;
    std::string mysqlHost = "tcp://127.0.0.1:3306";
    std::string mysqlUser = "your_user";
    std::string mysqlPassword = "your_password";
    std::string mysqlDatabase = "your_database";

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(processRedisQueue, redisHost, redisPort, mysqlHost, mysqlUser, mysqlPassword, mysqlDatabase);
    }

    // 主线程不需要等待，因为子线程永不结束
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}