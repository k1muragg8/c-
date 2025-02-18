#include "my_header.h"
#include <iostream>

int main() {
    MyClass obj;
    obj.sayHello();

    std::string text = "Boost Libraries";
    std::string pattern = "(\\w+)\\s(\\w+)";

    if (obj.matchRegex(text, pattern)) {
        std::cout << "Regex match found!" << std::endl;
    }
    else {
        std::cout << "No match found." << std::endl;
    }

    return 0;
}