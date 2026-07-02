// ===========================================================================
//  《C++ Primer》2.5 节示例：类型别名 / auto / decltype
// ---------------------------------------------------------------------------
//  要点：
//    1. 类型别名：给已有类型起个新名字。
//         - typedef：传统写法  typedef double wages;
//         - using（C++11，推荐）：using wages = double;
//       using 更直观，尤其用于模板别名。注意：别名不能「部分替换」类型，
//       如 const pstring p; 中 p 是「指向 char 的 const 指针」而非 const char*。
//    2. auto（C++11）：让编译器由初始值推导变量类型。
//         - auto 会「忽略顶层 const」，除非显式写出 const auto。
//         - auto 推导引用时，得到的是「所引用对象的类型」，而非引用本身。
//         - 要保留顶层 const / 引用语义，需在 auto 上显式加 const/&。
//    3. decltype（C++11）：从「表达式」推导类型，但与 auto 不同：
//         - 「保留」顶层 const 与引用，原样照搬。
//         - decltype(变量名)（不加括号）得到变量声明时的类型；
//           decltype((变量名))（加括号）对于变量总会得到「引用」类型，
//           因为「(变量)」是表达式而非变量名——这是易错点。
//
//  本程序：每个要点配一小段代码与输出。
// ===========================================================================
#include <iostream>
#include <typeinfo>

int main()
{
    // ---- 1. 类型别名：typedef vs using ----
    typedef double wages;            // 旧写法
    using   salary = double;         // 新写法（推荐），更接近 int x = ... 的形式
    wages  w = 3.14;
    salary s = 2.72;
    std::cout << "[别名] w=" << w << " (wages), s=" << s << " (salary)\n";
    std::cout << "  typeid(w) = " << typeid(w).name()
              << ", typeid(s) = " << typeid(s).name() << "\n\n";

    // 易错：别名用于 const 时的解读
    typedef char *pstring;           // pstring = 「指向 char 的指针」
    const pstring cstr = nullptr;    // cstr 是「const 的 pstring」
    // 即 cstr 本身是 const 指针 (char *const)，不是「指向 const char 的指针」。
    // 若误把别名替换成 char* 来「展开」��考：const char *cstr 是错的解读！
    // 正确理解：const 修饰「整个」pstring 类型（指针本身）。
    (void)cstr;

    // ---- 2. auto 类型推导 ----
    int   a = 10;
    int  &ra = a;
    const int ca = a;

    auto x1 = a;        // x1 是 int（普通变量）
    auto x2 = ra;       // x2 是 int（引用被忽略，得到所引对象类型）
    auto x3 = ca;       // x3 是 int（顶层 const 被忽略！）
    std::cout << "[auto 基础] x1=" << x1 << " x2=" << x2 << " x3=" << x3 << "\n";
    // 验证 x3 不是 const：可以赋值
    x3 = 99;
    std::cout << "  x3 赋值后 = " << x3 << " (说明 auto 忽略了顶层 const)\n";

    // 想保留顶层 const / 引用，需显式写出
    const auto  cx = ca;   // cx 是 const int
    auto       &rx = a;    // rx 是 int&（绑定到 a）
    // cx = 1;              // 错误：cx 是 const
    rx = 50;               // 通过引用修改 a
    std::cout << "  const auto cx=" << cx
              << ", auto& rx 修改后 a=" << a << "\n\n";

    // auto 与指针/引用结合：顶层 const 仍被忽略，底层 const 保留
    const int *pc = &a;       // pc 是「指向 const int 的指针」（底层 const）
    auto       y = pc;        // y 的类型是 const int*（底层 const 被保留！）
    std::cout << "[auto+指针] *y = " << *y
              << " (y 仍是指向 const int 的指针，底层 const 保留)\n";
    // *y = 1;               // 错误：*y 是 const int
    (void)y;

    // ---- 3. decltype 类型推导 ----
    int  d = 42;
    int &rd = d;
    const int cd = 7;

    decltype(d)  e1 = d;     // e1 是 int（原样照搬，顶层 const 也保留）
    (void)e1;                // 仅作演示，避免未使用变量警告
    decltype(rd) e2 = d;     // e2 是 int&（引用被保留！与 auto 不同）
    decltype(cd) e3 = 0;     // e3 是 const int（顶层 const 被保留！）
    e2 = 100;                // 通过引用 e2 修改 d
    // e3 = 1;               // 错误：e3 是 const
    std::cout << "[decltype] d=" << d << " (经 e2 修改), e3=" << e3 << " (const)\n";

    // 易错：decltype((变量)) 加了括号 → 得到引用
    decltype((d)) e4 = d;    // e4 是 int&（因为 (d) 是表达式）
    e4 = 200;                // 修改 d
    std::cout << "  decltype((d)) 是引用：d 经 e4 修改为 " << d << "\n\n";

    std::cout << "总结：\n"
              << "  auto   倾向于「简化」：忽略顶层 const、忽略引用；\n"
              << "  decltype倾向「忠实」：原样保留 const 与引用；\n"
              << "  decltype((v)) 与 decltype(v) 不同：前者恒为引用。\n";

    return 0;
}
