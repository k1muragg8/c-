#ifndef MY_HEADER_H
#define MY_HEADER_H

#include <string>

class MyClass {
public:
    void sayHello();
    bool matchRegex(const std::string& text, const std::string& pattern);
};

#endif // MY_HEADER_H