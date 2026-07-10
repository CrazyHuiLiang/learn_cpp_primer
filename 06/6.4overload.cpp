// ===========================================================================
//  《C++ Primer》6.4 节示例：函数重载
// ---------------------------------------------------------------------------
//  要点：
//    - 重载：同名函数，形参类型/个数不同。返回类型不参与重载判定。
//    - 顶层 const 形参不构成重载：
//        void g(int);    与  void g(const int);     重复定义（实参按值传递，
//        顶层 const 仅作用于局部拷贝，调用方无法区分）。
//    - 底层 const 形参构成重载：
//        void h(int&);   与  void h(const int&);    是两个不同函数。
//    - 重载与 const_cast 相互调用：常版本承担实际工作，非常版本用
//      const_cast 转调常版本，避免代码重复（书中 shortToConstCast 模式）。
// ===========================================================================
#include <iostream>
#include <string>

// 1) 按形参类型重载
void print(int x)             { std::cout << "print(int):             " << x << std::endl; }
void print(double x)          { std::cout << "print(double):          " << x << std::endl; }
void print(const std::string &s) { std::cout << "print(const string&):  " << s << std::endl; }

// 2) 底层 const 构成重载：引用/指针指向的对象是否 const
void lookup(std::string &s)       { std::cout << "lookup(string&):       non-const: " << s << std::endl; }
void lookup(const std::string &s) { std::cout << "lookup(const string&): const:     " << s << std::endl; }

// 3) 重载与 const_cast 相互调用：常版本做实际工作，非常版本转调
const std::string &shorter_string(const std::string &a, const std::string &b)
{
    return a.size() <= b.size() ? a : b;   // 返回 const 引用
}

// 非常版本：参数是非 const 引用，希望返回非 const 引用供调用方修改
std::string &shorter_string(std::string &a, std::string &b)
{
    // 转调常版本：把 a、b 转成 const 引用，再把返回的 const 引用 const_cast 回去
    // 这里安全：调用方传入的 a、b 本就是非 const 对象
    auto &r = shorter_string(const_cast<const std::string&>(a),
                             const_cast<const std::string&>(b));
    return const_cast<std::string&>(r);
}

int main()
{
    // 1) 按类型重载
    print(42);
    print(3.14);
    print(std::string("hello"));

    // 2) const 形参重载
    std::string s1 = "modifiable";
    const std::string s2 = "readonly";
    lookup(s1);   // 非 const 对象 -> lookup(string&)
    lookup(s2);   // const   对象 -> lookup(const string&)

    // 3) const_cast 模式
    std::string x = "short";
    std::string y = "longer!";
    std::string &r = shorter_string(x, y);   // 调用非常版本
    r += "???";                              // 可修改（r 绑定到 x）
    std::cout << "x = " << x << std::endl;
    return 0;
}
