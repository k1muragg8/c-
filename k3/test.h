#ifndef TEST_H  // 头文件保护：如果 TEST_H 没有被定义
#define TEST_H  // 定义 TEST_H，防止重复包含

class MyClass { // 定义一个名为 MyClass 的类
public:
  MyClass(int value); // 公有构造函数声明，接受一个整数参数
  int getValue();      // 公有成员函数声明，返回一个整数
private:
  int value_;         // 私有成员变量，存储整数值
};

int add(int a, int b); // 公有函数声明，接受两个整数参数，返回一个整数

#endif // 结束头文件保护