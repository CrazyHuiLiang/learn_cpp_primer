// ===========================================================================
//  《C++ Primer》5.5 节示例：标准异常类层次
// ---------------------------------------------------------------------------
//  本程序：演示 <stdexcept> 中几个常用异常类的抛出与捕获：
//    - std::runtime_error        运行时错误（如除零）
//    - std::invalid_argument     参数不合法（logic_error 的派生类）
//    - std::out_of_range         下标越界（logic_error 的派生类）
//  并展示用基类 std::exception 的引用多态捕获所有派生异常。
//
//  异常类层次（<stdexcept> 与 <exception>）：
//      std::exception                         （<exception> 头文件，基类）
//        ├── std::logic_error                 （<stdexcept>，可在编写时避免）
//        │     ├── std::invalid_argument
//        │     ├── std::out_of_range
//        │     ├── std::length_error
//        │     └── std::domain_error
//        └── std::runtime_error               （<stdexcept>，运行时才显现）
//              ├── std::overflow_error
//              ├── std::underflow_error
//              └── std::range_error
//  每个异常类都提供一个 what() 成员，返回 const char* 描述信息。
//  因为它们都派生自 std::exception，所以 catch (const std::exception &e)
//  可以统一捕获上面所有异常（多态）。
// ===========================================================================
#include <iostream>
#include <stdexcept>               // runtime_error / logic_error / invalid_argument / out_of_range
#include <string>
#include <vector>

// 三个分别抛出不同标准异常的函数
int safeDivide(int a, int b)
{
    if (b == 0)
        throw std::runtime_error("safeDivide: 除数为 0");   // runtime_error
    return a / b;
}

int parsePositive(const std::string &s)
{
    int v = std::stoi(s);          // 字符串转整数
    if (v <= 0)
        throw std::invalid_argument("parsePositive: 需要正整数"); // logic_error 派生
    return v;
}

int safeAt(const std::vector<int> &v, std::size_t idx)
{
    if (idx >= v.size())
        throw std::out_of_range("safeAt: 下标越界");        // logic_error 派生
    return v[idx];
}

int main()
{
    // ---------- 演示 1：分别捕获各类异常 ----------
    // 逐个触发：注释切换可看到不同的 what() 信息
    try {
        // 触发 runtime_error
        // std::cout << safeDivide(10, 0) << std::endl;

        // 触发 invalid_argument
        // std::cout << parsePositive("-5") << std::endl;

        // 触发 out_of_range
        std::vector<int> v = {1, 2, 3};
        std::cout << safeAt(v, 10) << std::endl;
    } catch (const std::runtime_error &e) {
        std::cerr << "[runtime_error] " << e.what() << std::endl;
    } catch (const std::invalid_argument &e) {
        std::cerr << "[invalid_argument] " << e.what() << std::endl;
    } catch (const std::out_of_range &e) {
        std::cerr << "[out_of_range] " << e.what() << std::endl;
    }

    // ---------- 演示 2：用基类 std::exception 统一捕获 ----------
    // 由于 runtime_error / logic_error 都派生自 std::exception，
    // 一个 catch (const std::exception &) 即可多态捕获所有标���异常。
    // 注意：catch 子句按顺序匹配，派生类应写在基类前面，否则会被基类先吃掉。
    try {
        // 任选其一触发：
        // std::cout << safeDivide(10, 0) << std::endl;
        // std::cout << parsePositive("0") << std::endl;
        std::vector<int> v = {1, 2, 3};
        std::cout << safeAt(v, 100) << std::endl;
    } catch (const std::exception &e) {
        // 基类引用多态捕获：e.what() 实际调用的是派生类版本
        std::cerr << "[std::exception] " << e.what() << std::endl;
    }

    return 0;
}
