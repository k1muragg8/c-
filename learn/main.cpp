#include <iostream>
#include <stdexcept>
using namespace std;

int tryCatch(double num, double deo)
{
    try {
        if (num < 0 or deo < 0){
            throw std::runtime_error("num must be > 0");
        }
        double result = num / deo;
        std::cout << "result: " << result << std::endl;
    }catch (const exception& e) {
        std::cout << "error is: " << e.what() << std::endl;
    }
    return 0;
}

int add(int a, int b)
{
    return a + b;
}

int main()
{
    int result = add(3, 4);
    double resule2 = tryCatch(3.4, -4);
    std::cout << "Result: " << result << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
