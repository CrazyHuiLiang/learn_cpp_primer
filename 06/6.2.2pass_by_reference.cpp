// ===========================================================================
//  《C++ Primer》6.2 节示例：引用形参（pass by reference）
// ---------------------------------------------------------------------------
//  要点：
//    - 引用形参绑定到实参对象本身，函数内修改引用即修改实参。
//    - 用引用形参可避免拷贝大对象（如 std::string、容器）。
//    - 用引用形参可一次返回多个结果（除返回值外，再通过引用形参带出）。
//
//  本程序：
//    1) reset(int &i) 真正修改外部变量；
//    2) compare_string(const std::string&) 避免拷贝大对象；
//    3) divide(int, int, int &quot, int &rem) 用引用形参返回商和余数。
// ===========================================================================
#include <iostream>
#include <string>

// 引用形参：i 绑定到调用处的实参，置 0 会真正改变外部变量
void reset(int &i)
{
    i = 0;
}

// 避免拷贝大对象：const 引用形参只读不拷贝
// 若写成 std::string s，每次调用都会拷贝整个字符串
bool is_longer_than(const std::string &s, std::string::size_type n)
{
    return s.size() > n;
}

// 用引用形参返回多个结果：同时带出商和余数
void divide(int dividend, int divisor, int &quot, int &rem)
{
    quot = dividend / divisor;
    rem  = dividend % divisor;
}

int main()
{
    // 1) 引用形参真正修改外部变量
    int n = 42;
    std::cout << "before reset: n = " << n << std::endl;   // 42
    reset(n);
    std::cout << "after  reset: n = " << n << std::endl;   // 0

    // 2) 避免拷贝大对象
    std::string text = "hello C++ Primer";
    std::cout << "text is longer than 5 chars? "
              << std::boolalpha << is_longer_than(text, 5) << std::endl;

    // 3) 用引用形参返回多个结果
    int q = 0, r = 0;
    divide(17, 5, q, r);   // 17 / 5 = 3 余 2
    std::cout << "17 / 5 = " << q << " rem " << r << std::endl;
    return 0;
}
