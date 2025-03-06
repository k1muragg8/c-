#include "MySQLDatabase.h"

int main() {
    MySQLDatabase db("192.168.0.69", "k1", "ab$BHT5;o", "eat", 3306);

    if (db.connect()) {
        if (db.query("select * from e_food_store")) {
            db.printResult();
        }
    }

    return 0;
}