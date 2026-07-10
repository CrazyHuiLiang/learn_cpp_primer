// ===========================================================================
//  《C++ Primer》6.3 节示例：返回值
// ---------------------------------------------------------------------------
//  要点：
//    - 值返回：返回的是局部对象的一份拷贝（或通过移动返回）。
//    - 引用返回：返回引用本身，可作左值、支持链式调用（如 vector::operator[]）。
//    - 重要原则：不要返回局部对象的引用或指针——局部对象在函数返回后销毁，
//      返回的引用/指针会变成悬空引用。可返回：局部对象的值、静态/堆对象的
//      引用、形参引用（如形参是引用且其绑定对象生命周期超出函数）。
//    - 返回 const 引用可避免返回的对象被修改。
// ===========================================================================
#include <iostream>
#include <string>
#include <vector>
#include <cctype>   // std::toupper

// 值返回：返回局部对象的拷贝
std::string make_greeting(const std::string &name)
{
    std::string msg = "Hello, " + name + "!";   // 局部对象
    return msg;                                  // 返回 msg 的拷贝（移动）
}

// 引用返回：形参引用绑定到外部对象，返回其引用可作左值
// （不要返回局部对象的引用——这里返回的是形参引用，安全）
std::string &to_upper(std::string &s)
{
    for (auto &c : s) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    return s;   // 返回 s 的引用，可继续作左值
}

// 返回 const 引用：调用方不能通过返回值修改对象
const std::string &pick(const std::string &a, const std::string &b)
{
    return a.size() < b.size() ? a : b;   // 返回两个形参引用中较短者
}

int main()
{
    // 1) 值返回
    std::cout << make_greeting("C++") << std::endl;

    // 2) 引用返回作左值 + 链式调用
    std::string s = "hello";
    to_upper(s) += "!!";   // to_upper 返回引用，可作左值
    std::cout << s << std::endl;

    std::vector<std::string> v = {"alpha", "beta", "gamma"};
    v[0] = "ALPHA";         // operator[] 返回引用，可作左值
    std::cout << v[0] << std::endl;

    // 3) 返回 const 引用：不能通过返回值修改对象
    //    注意：pick 返回形参引用，因此实参必须是生命周期足够长的命名对象，
    //    不能传临时对象（否则引用悬空）。这里 a、b 是 main 的局部对象，
    //    生命周期覆盖 r 的使用期，安全。
    std::string a = "short";
    std::string b = "longer!";
    const std::string &r = pick(a, b);   // 返回对 a 的 const 引用
    std::cout << "shorter: " << r << std::endl;
    // r += "x";  // 编译错误：const 引用不能被修改
    return 0;
}
