#include "my_header.h"
#include <iostream>
#include <boost/regex.hpp>

void MyClass::sayHello() {
    std::cout << "Hello, World!" << std::endl;
}

bool MyClass::matchRegex(const std::string& text, const std::string& pattern) {
    boost::regex expr(pattern);
    return boost::regex_match(text, expr);
}