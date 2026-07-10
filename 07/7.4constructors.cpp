// ===========================================================================
//  《C++ Primer》7.4 节示例：构造函数
// ---------------------------------------------------------------------------
//  要点：
//    1. 构造函数初始值列表（initializer list）的必要性：
//       - const 成员、引用成员、没有默认构造函数的类类型成员，
//         必须「初始化」而非「赋值」，因此只能用初始值列表，
//         不能在构造函数体内赋值。
//    2. 合成默认构造函数何时失效：
//       - 一旦类定义了任何构造函数，编译器就不再自动合成默认构造。
//       - 此时若还需要默认构造，必须显式写 Sales_data() = default;。
//    3. =default 的用法：
//       - 显式要求编译器合成默认构造函数，保持类内初始值生效。
//
//  本例定义一个 ConstRef 类：包含 const 成员与引用成员，演示必须用
//  构造函数初始值列表；并对比「有自定义构造则不再合成默认构造」。
// ===========================================================================
#include <iostream>
#include <string>

// ---- 演示：必须用构造函数初始值列表的类 ----
class ConstRef
{
public:
    // 正确：用初始值列表初始化 ci（const int）、ri（int&）、val
    //   - ci 是 const，只能初始化不能赋值
    //   - ri 是引用，必须在初始化时绑定，之后不能重新绑定
    //   - 因此这两者都不能在函数体内用 = 赋值
    ConstRef(int v, int &r) : ci(v), ri(r), val(v) {}

    // 错误写法示意（编译不过，故注释）：
    //   ConstRef(int v, int &r) { val = v; }   // ci、ri 未初始化 → 编译错误
    //     因为 ci 是 const、ri 是引用，二者都「必须初始化」，
    //     进入函数体时它们尚未被初始化，已为时已晚。

    void show() const
    {
        std::cout << "val=" << val << " ci=" << ci << " ri=" << ri << std::endl;
    }

    // 提供 const 访问器，让外部可读 ri（ri 是引用，绑定到构造时传入的对象）
    const int &ri_value() const { return ri; }

private:
    int        val;   // 普通成员
    const int  ci;    // const 成员：必须用初始值列表
    int       &ri;    // 引用成员：必须用初始值列表
};

// ---- 演示：有自定义构造则不再合成默认构造 ----
class HasCtor
{
public:
    // 一旦定义了这个构造函数，编译器就不再合成默认构造 HasCtor()���
    HasCtor(int x) : x_(x) {}
    int get() const { return x_; }
private:
    int x_;
};

int main()
{
    int n = 42;
    ConstRef cr(10, n);          // 必须提供实参初始化 const 成员与引用成员
    cr.show();                   // val=10 ci=10 ri=42

    n = 99;                      // 改变 n，ri 是 n 的引用，输出也会变
    std::cout << "改 n 后 ri=" << cr.ri_value()
              << "（ri 绑定到 n，n 变则 ri 变）" << std::endl;

    // ---- 有自定义构造则不再合成默认构造 ----
    HasCtor hc(7);               // 合法：用自定义构造
    std::cout << "hc.x=" << hc.get() << std::endl;

    // HasCtor bad;               // 错误：无默认构造函数（被自定义构造取代）
    //   若需要默认构造，应在类中显式写 HasCtor() = default; 或 HasCtor() {...}。

    return 0;
}
