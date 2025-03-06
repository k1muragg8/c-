#include "test.h" // 包含 test.h 头文件，以便使用其中声明的类和函数
#include <iostream> // 包含 iostream 头文件，以便使用 std::cout

MyClass::MyClass(int value) : value_(value) {} // MyClass 类的构造函数实现，使用成员初始化列表初始化 value_

int MyClass::getValue() { // MyClass 类的 getValue() 函数实现
    return value_;         // 返回私有成员变量 value_ 的值
}

int add(int a, int b) { // add() 函数实现
    return a + b;        // 返回两个整数参数的和
}