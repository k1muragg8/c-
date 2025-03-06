//
// Created by k1mura on 25-2-28.
//

#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H

#include <iostream>
#include <iomanip>
#include <mysql.h>
#include <vector>
#include <cstring>

class MySQLDatabase {
public:
    MySQLDatabase(const char* host, const char* user, const char* password, const char* database, unsigned int port);
    ~MySQLDatabase();

    bool connect();
    bool query(const char* sql);
    void printResult();

private:
    MYSQL* conn;
    MYSQL_RES* res;

    const char* host;
    const char* user;
    const char* password;
    const char* database;
    unsigned int port;
};



#endif //MYSQLDATABASE_H
