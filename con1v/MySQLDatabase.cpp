//
// Created by k1mura on 25-2-28.
//

#include "MySQLDatabase.h"
MySQLDatabase::MySQLDatabase(const char* host, const char* user, const char* password, const char* database, unsigned int port)
    : host(host), user(user), password(password), database(database), port(port), conn(nullptr), res(nullptr) {}

MySQLDatabase::~MySQLDatabase() {
    if (res) mysql_free_result(res);
    if (conn) mysql_close(conn);
}

bool MySQLDatabase::connect() {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        std::cerr << "Error initializing MySQL connection" << std::endl;
        return false;
    }

    if (mysql_real_connect(conn, host, user, password, database, port, NULL, 0) == NULL) {
        std::cerr << "Error connecting to MySQL server: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        conn = nullptr;
        return false;
    }

    return true;
}

bool MySQLDatabase::query(const char* sql) {
    if (mysql_query(conn, sql)) {
        std::cerr << "Error executing query: " << mysql_error(conn) << std::endl;
        return false;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        std::cerr << "Error getting result: " << mysql_error(conn) << std::endl;
        return false;
    }

    return true;
}

void MySQLDatabase::printResult() {
    int num_fields = mysql_num_fields(res);
    std::vector<int> column_widths(num_fields, 20);

    MYSQL_FIELD* fields = mysql_fetch_fields(res);
    std::vector<std::string> field_names(num_fields);
    for (int i = 0; i < num_fields; i++) {
        field_names[i] = fields[i].name;
        column_widths[i] = std::max(column_widths[i], static_cast<int>(field_names[i].length()) + 2);
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < num_fields; i++) {
            int length = row[i] ? strlen(row[i]) : 4;
            column_widths[i] = std::max(column_widths[i], length + 2);
        }
    }

    std::cout << "+";
    for (int width : column_widths) {
        std::cout << std::string(width, '-') << "+";
    }
    std::cout << std::endl;

    std::cout << "|";
    for (int i = 0; i < num_fields; i++) {
        std::cout << std::left << std::setw(column_widths[i]) << field_names[i] << "|";
    }
    std::cout << std::endl;

    std::cout << "+";
    for (int width : column_widths) {
        std::cout << std::string(width, '-') << "+";
    }
    std::cout << std::endl;

    mysql_data_seek(res, 0);
    while ((row = mysql_fetch_row(res))) {
        std::cout << "|";
        for (int i = 0; i < num_fields; i++) {
            std::cout << std::left << std::setw(column_widths[i]) << (row[i] ? row[i] : "NULL") << "|";
        }
        std::cout << std::endl;
    }

    std::cout << "+";
    for (int width : column_widths) {
        std::cout << std::string(width, '-') << "+";
    }
    std::cout << std::endl;
}