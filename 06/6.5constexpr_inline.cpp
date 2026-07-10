// ===========================================================================
//  《C++ Primer》6.5 节示例：constexpr 与 inline 函数
// ---------------------------------------------------------------------------
//  要点：
//    - constexpr 函数：返回值是常量表达式，可在编译期求值。
//        * 限制（C++17 已放宽）：函数体通常单一 return；C++14/17 起允许
//          局部变量、循环、条件等。形参和返回类型必须是字面值类型。
//        * 调用时若实参为常量表达式，可在编译期求值；否则退化为运行期求值。
//    - inline 函数：通常定义在头文件中，编译时在调用处展开，避免 ODR
//      （单一定义规则）问题——inline 允许同一函数定义出现在多个翻译单元。
//      适合短小、频繁调用的函数。
//
//  本程序各配示例。
// ===========================================================================
#include <iostream>
#include <cmath>

// constexpr 函数：实参为常量时可在编译期求值
constexpr int square(int x) { return x * x; }

// constexpr 函数：可递归（C++14/17）
constexpr int factorial_cx(int n)
{
    return (n <= 1) ? 1 : n * factorial_cx(n - 1);
}

// inline 函数：短小函数，定义放头文件可被多个 .cpp 包含
inline double distance(double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

int main()
{
    // 1) constexpr 编译期求值：可用于常量表达式场景（数组长度、模板参数等）
    constexpr int s5 = square(5);          // 编译期求值，s5 == 25
    int arr[square(3)] = {0};              // 用作数组长度
    std::cout << "square(5) = " << s5 << std::endl;
    std::cout << "sizeof(arr) = " << sizeof(arr) << std::endl;

    constexpr int f6 = factorial_cx(6);    // 720，编译期求值
    std::cout << "factorial_cx(6) = " << f6 << std::endl;

    // 2) 实参不是常量时，constexpr 函数在运行期求值
    int n = 0;
    std::cin >> n;                         // 运行期输入
    std::cout << "square(n) = " << square(n) << std::endl;   // 运行期

    // 3) inline 函数
    std::cout << "distance = " << distance(0.0, 0.0, 3.0, 4.0) << std::endl;  // 5
    return 0;
}
