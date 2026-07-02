// ===========================================================================
//  《C++ Primer》2.4 节示例：const 与顶层/底层 const
// ---------------------------------------------------------------------------
//  要点：
//    1. const 对象：创建后其值不可修改，因此「必须初始化」，且初始化可用
//       任意表达式（包括非 const）。默认 const 对象仅在当前文件有效，多文件
//       共享要用 extern（这里不展开）。
//    2. 对 const 的引用（常量引用 const T&）：
//         - 可绑定到 const 对象、非 const 对象、字面值、表达式结果。
//         - 通过它不能修改所绑定的对象（哪怕原对象本身非 const）。
//         - 这是 C++ 最常用的「只读形参」形式。
//    3. 指针与 const 有两种组合，务必分清：
//         - 指向 const 的指针：const int *p / int const *p
//             「不能通过 p 改所指对象」，但 p 可改指向别的对象。
//         - const 指针：int *const p
//             p 本身是 const，一旦指向某对象就不可再改，但可通过 *p 修改对象。
//    4. 【核心概念】顶层 const(top-level) vs 底层 const(low-level)：
//         - 顶层 const：指针对象「本身」是 const（如 int *const p）。
//                       也泛指任意对象本身是 const（如 const int i）。
//         - 底层 const：指针「所指对象」是 const（如 const int *p），
//                       或引用所绑定的对象是 const。
//         区分意义：拷贝时「顶层 const 可忽略」，但「底层 const 必须匹配」。
//
//  本程序：演示上述各点，并用代码显式区分顶层/底层 const。
// ===========================================================================
#include <iostream>

int main()
{
    // ---- 1. const 对象创建后不可修改 ----
    const int bufSize = 512;   // 必须初始化
    // bufSize = 600;          // 错误：不能给 const 赋值
    std::cout << "bufSize = " << bufSize << "\n";

    // ---- 2. 对 const 的引用（常量引用）----
    const int &r1 = bufSize;   // OK：常量引用绑定到 const 对象
    const int &r2 = 42;        // OK：可绑定到字面值（非常量引用不行！）
    const int &r3 = r1 * 2;    // OK：可绑定到表达式结果
    (void)r2; (void)r3;        // 仅作演示，避免未使用变量警告
    int i = 10;
    const int &r4 = i;         // OK：常量引用也可绑定到「非 const」对象
    // r4 = 20;                // 错误：通过常量引用不能修改所绑定对象
    i = 20;                    // 但通过 i 本身仍可改（i 不是 const）
    std::cout << "r4 = " << r4 << " (随 i 改变)\n\n";
    // 注意：r4 绑定 i 后，i 仍可变；只是「不能通过 r4」去改。

    // ---- 3. 指向 const 的指针 vs const 指针 ----
    const int ci = 0;
    const int *p1 = &ci;       // 指向 const 的指针：不能通过 p1 改 ci
    (void)p1;                  // 仅作演示
    // *p1 = 1;                // 错误：不能通过指向 const 的指针赋值
    int j = 5;
    p1 = &j;                   // OK：p1 本身不是 const，可改指向
    // *p1 = 6;                // 仍错误：即便指向非 const 的 j，也不能通过 p1 改

    int *const p2 = &j;        // const 指针：p2 本身不可改指向
    *p2 = 6;                   // OK：可通过 p2 修改所指对象 j
    // p2 = &i;                // 错误：p2 本身是 const，不能改指向
    std::cout << "j = " << j << " (经 const 指针 p2 改为 6)\n\n";

    // ---- 4. 顶层 const vs 底层 const ----
    int v = 10;
    const int cv = 10;         // 顶层 const（对象本身是 const）
    (void)cv;                  // 仅作演示

    const int *lp = &v;        // 底层 const：所指对象被当作 const（p 本身可改）
    int *const tp = &v;        // 顶层 const：指针本身是 const（所指对象可改）
    const int *const bp = &v;  // 既有顶层（指针本身）又有底层（所指对象）

    std::cout << "顶层/底层 const 均可正常使用：\n";
    std::cout << "  *lp = " << *lp << "\n";
    std::cout << "  *tp = " << *tp << "\n";
    std::cout << "  *bp = " << *bp << "\n\n";

    // 拷贝规则演示：
    //   顶层 const 在拷贝时会被忽略（因为拷贝不改变原对象）。
    const int a1 = 1;
    int a2 = a1;               // OK：把 const int 拷给 int，顶层 const 被忽略
    std::cout << "a2 = " << a2 << " (顶层 const 拷贝时被忽略)\n";

    //   底层 const 必须匹配：非常量可转常量，反之不行。
    int *p3 = &v;
    const int *p4 = p3;        // OK：int* → const int*（增加底层 const）
    // int *p5 = p4;           // 错误：const int* → int* 会丢底层 const
    (void)p3; (void)p4;
    std::cout << "(底层 const 在拷贝时必须匹配：增 const 允许，减 const 不允许)\n";

    return 0;
}
