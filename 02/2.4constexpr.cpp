// ===========================================================================
//  《C++ Primer》2.4 节示例：constexpr 与常量表达式
// ---------------------------------------------------------------------------
//  要点：
//    1. 「常量表达式(constant expression)」：值在「编译期」就能确定、且
//       类型是整型/浮点字面量类型的表达式。如 20、20+30、sizeof(int)。
//    2. const 不一定是常量表达式：
//         const int sz = get_size();   // 运行期才知道值 → 不是常量表达式
//         const int sz2 = 20;          // 编译期已知 → 是常量表达式
//       即 const 只保证「运行期不可改」，不保证「编译期可求值」。
//    3. constexpr 变量：声明为 constexpr 的变量「一定是常量表达式」，编译器
//       会在编译期对其初始化式求值，若无法在编译期求值则报错。
//       因此能用 constexpr 就优先用，比 const 更「严格」也更安全。
//    4. constexpr 与指针：
//         constexpr 修饰指针时，「只对指针本身有效」(顶层 const)，
//         不涉及所指对象是否 const。
//         即 constexpr int *p 表示「p 是个编译期已知的、不可改指向的指针」，
//         所指对象可以是非 const 的 int。
//
//  本程序：演示 constexpr 变量、constexpr 指针，并与 const 对比。
// ===========================================================================
#include <iostream>

// constexpr 函数：若参数都是常量表达式，返回值也是常量表达式（编译期求值）。
// （C++14 起函数体可含更多语句，这里用最简单的形式。）
constexpr int square(int x) { return x * x; }

int main()
{
    // ---- 1. constexpr 变量：编译期可求值 ----
    constexpr int mf  = 20;          // 20 是字面量 → 常量表达式
    constexpr int limit = mf + 1;    // mf+1 仍是常量表达式
    constexpr int sz  = square(5);   // square(5) 在编译期可求值 → 25
    std::cout << "mf = " << mf << ", limit = " << limit
              << ", sz = " << sz << "\n\n";

    // ---- 2. const vs constexpr 的区别 ----
    int runtime_val = 0;
    std::cout << "输入一个整数: ";
    std::cin >> runtime_val;         // 运行期才知道值
    const int c1 = runtime_val;      // OK：const 不要求编译期已知 → 不是常量表达式
    // constexpr int c2 = runtime_val; // 错误！runtime_val 不是常量表达式
    std::cout << "const c1 = " << c1
              << " (运行期确定，不是常量表达式)\n\n";
    // 结论：const = 「不可改」；constexpr = 「不可改 且 编译期可求值」。
    //       constexpr 是 const 的超集：constexpr 一定也是 const。

    // ---- 3. constexpr 指针：仅对指针本身是顶层 const ----
    int v = 10;
    (void)v;                    // 仅作演示用，避免未使用变量警告
    // constexpr 修饰指针 → 指针本身不可改指向（顶层 const），
    // 所指对象是否 const 要看「类型」：这里是 int*，所以所指对象非 const。
    constexpr int *p = nullptr;      // 编译期已知的空地址（仅作演示）
    (void)p;

    // 更实际的例子：把「全局/静态对象的地址」赋给 constexpr 指针。
    // 注意：局部非静态变量(如上面的 v)的地址在编译期无法确定，
    //       不能用来初始化 constexpr 指针；静态对象才可以。
    static int global_like = 5;      // 静态对象，地址编译期可确定
    constexpr int *cp = &global_like;// OK：cp 是 const 指针，指向 global_like
    *cp = 50;                        // OK：所指对象非 const，可改值
    // cp = nullptr;                 // 错误：cp 本身是 constexpr(顶层 const)
    std::cout << "global_like = " << global_like
              << " (经 constexpr 指针 cp 修改为 50)\n";

    return 0;
}
