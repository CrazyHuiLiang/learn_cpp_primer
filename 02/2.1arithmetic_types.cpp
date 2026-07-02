// ===========================================================================
//  《C++ Primer》2.1 节示例：内置算术类型与隐式转换陷阱
// ---------------------------------------------------------------------------
//  要点：
//    1. C++ 内置算术类型分两大类：整型（bool / char / short / int / long ...）
//       与浮点型（float / double / long double）。各类型占用的字节数由实现
//       决定，可用 sizeof 查询。
//    2. 整型除 bool 外都有「有符号(signed)」与「无符号(unsigned)」两种。
//       无符号类型不能表示负数，但同样位数下能表示的正数范围翻倍。
//    3. 【重点陷阱】当一个无符号数与一个有符号数一起运算时，有符号数会被
//       「隐式转换」成无符号数。若该有符号数是负数，转换后会变成一个巨大
//       的正数（取模后的结果），导致结果完全出乎意料。
//       规则：有符号 + 无符号 → 按无符号运算（含负数也被解释为无符号）。
//
//  本程序：用 sizeof 打印各类型大小，并演示无符号/有符号混合运算的陷阱。
// ===========================================================================
#include <iostream>

int main()
{
    // ---- 1. 各算术类型的大小（字节数随编译器/平台而异）----
    std::cout << "sizeof(bool)         = " << sizeof(bool) << "\n";
    std::cout << "sizeof(char)         = " << sizeof(char) << "\n";
    std::cout << "sizeof(short)        = " << sizeof(short) << "\n";
    std::cout << "sizeof(int)          = " << sizeof(int) << "\n";
    std::cout << "sizeof(long)         = " << sizeof(long) << "\n";
    std::cout << "sizeof(long long)    = " << sizeof(long long) << "\n";
    std::cout << "sizeof(float)        = " << sizeof(float) << "\n";
    std::cout << "sizeof(double)       = " << sizeof(double) << "\n";
    std::cout << "sizeof(long double)  = " << sizeof(long double) << "\n\n";

    // ---- 2. 有符号 vs 无符号：同样位数，能表示的范围不同 ----
    unsigned char uc = 255;          // 8 位无符号：范围 0 ~ 255
    signed   char sc = -1;           // 8 位有符号：范围 -128 ~ 127
    std::cout << "unsigned char uc = " << static_cast<int>(uc) << "\n";
    std::cout << "signed   char sc = " << static_cast<int>(sc) << "\n\n";
    // 注意：char 直接输出会被当作字符，所以转成 int 打印才看得到数值

    // ---- 3. 【核心陷阱】无符号与有符号混合运算 ----
    unsigned u = 10;
    int      i = -42;

    // u + i ：i 会先被转成 unsigned。
    //   在 32 位 int 上，-42 转成 unsigned 是 4294967254（即 2^32 - 42），
    //   再加 10 得 4294967264，远不是预期的 -32。
    std::cout << "u + i  = " << u + i << "\n";   // 输出一个巨大的正数
    // 直接输出 i 仍是 -42，因为 i 本身类型没变
    std::cout << "i      = " << i << "\n\n";

    // ---- 4. 无符号数「永远 >= 0」带来的循环陷阱 ----
    // 经典错误：用 unsigned 作递减循环变量
    //   for (unsigned k = 10; k >= 0; --k) { ... }
    // 当 k 减到 0 再 -- 时会「环绕」回 unsigned 的最大值，循环永不结束！
    // 正确写法：用能取负值的类型，或改用条件判断。
    unsigned k = 0;
    std::cout << "unsigned k=0, --k = " << --k << "\n";  // 环绕成 UINT_MAX
    // 教训：千万不要把无符号类型用于可能涉及负数的运算或递减循环。

    return 0;
}
