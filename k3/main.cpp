#include "test.h"      // 包含 test.h 头文件，以便使用其中声明的类和函数
#include <iostream> // 包含 iostream 头文件，以便使用 std::cout

int main() {
    MyClass obj(10); // 创建 MyClass 类的对象 obj，并使用构造函数初始化 value_ 为 10
    std::cout << "Value: " << obj.getValue() << std::endl; // 调用 obj 的 getValue() 函数，并输出返回值

    int result = add(5, 7); // 调用 add() 函数，并将返回值赋给 result
    std::cout << "Result: " << result << std::endl; // 输出 result 的值

    return 0; // 程序正常结束
}