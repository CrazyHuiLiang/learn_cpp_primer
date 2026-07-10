// ===========================================================================
//  《C++ Primer》4.8 节示例：位运算符
// ---------------------------------------------------------------------------
//  要点：
//    1. 位运算符（操作数按「二进制位」处理，整型/字符型）：
//         ~   按位取反（一元）
//         <<  左移   （右端补 0；对有符号数的符号位移动为 UB，建议仅用于无符号）
//         >>  右移   （无符号数高位补 0；有符号数「算术/逻辑」由实现定义）
//         &   按位与
//         ^   按位异或（相同为 0，不同为 1）
//         |   按位或
//       优先级：~ 高于 << >> 高于 & 高于 ^ 高于 |
//       （注意 & ^ | 的优先级都低于关系运算符，写条件时要加括号！）
//    2. 位运算「不改变操作数本身」，只是产生一个新值；
//       要保留结果需用复合赋值：<<=  >>=  &=  ^=  |=
//    3. 移位语义：
//       - 左移 n 位等价于「乘 2^n」（在不溢出时）。
//       - 右移 n 位对无符号数等价于「除 2^n」向下取整。
//       - 移位位数 >= 类型位宽时为 UB。
//    4. 位掩码(mask)常用技术：
//       - 打开(置1)某位：x |= (1u << n)
//       - 关闭(清0)某位：x &= ~(1u << n)
//       - 翻转某位    ：x ^= (1u << n)
//       - 测试某位    ：(x >> n) & 1u  或  bool(x & (1u << n))
// ===========================================================================
#include <iostream>
#include <cstdint>

// 以 8 位二进制打印一个 unsigned 值（方便观察位运算结果）
void print_bits8(unsigned int v)
{
    for (int i = 7; i >= 0; --i) {
        std::cout << ((v >> i) & 1u);
    }
}

int main()
{
    // --- 基本位运算 ---
    unsigned char a = 0b0011'1010;   // 0x3A = 58
    unsigned char b = 0b0101'0101;   // 0x55 = 85

    std::cout << "a      = "; print_bits8(a); std::cout << "  (0x3A)\n";
    std::cout << "b      = "; print_bits8(b); std::cout << "  (0x55)\n";

    std::cout << "~a     = "; print_bits8(static_cast<unsigned char>(~a));
    std::cout << "  (按位取反)\n";

    std::cout << "a & b  = "; print_bits8(static_cast<unsigned char>(a & b));
    std::cout << "  (按位与：同为 1 才为 1)\n";

    std::cout << "a | b  = "; print_bits8(static_cast<unsigned char>(a | b));
    std::cout << "  (按位或：任一为 1 即为 1)\n";

    std::cout << "a ^ b  = "; print_bits8(static_cast<unsigned char>(a ^ b));
    std::cout << "  (按位异或：不同为 1)\n";

    // --- 移位 ---
    std::cout << "\n--- 移位运算 ---\n";
    unsigned int x = 0b0000'0001;     // 1
    std::cout << "x          = "; print_bits8(x); std::cout << '\n';
    std::cout << "x << 3     = "; print_bits8(x << 3);
    std::cout << "  (左移 3 位：相当于 *8)\n";
    std::cout << "(x << 3) 后 x 仍为 "; print_bits8(x);
    std::cout << "  —— 位运算不改变操作数本身\n";

    // 用复合赋值才保留结果
    x <<= 3;
    std::cout << "x <<= 3 后 x = "; print_bits8(x); std::cout << '\n';

    std::cout << "x >> 1     = "; print_bits8(x >> 1);
    std::cout << "  (右移 1 位：相当于 /2)\n";

    // --- 掩码技术：对「某一位」做操作 ---
    std::cout << "\n--- 掩码技术（对第 n 位操作，n 从 0 起）---\n";
    unsigned int flags = 0b0000'0000;   // 初始全 0
    std::cout << "初始 flags = "; print_bits8(flags); std::cout << '\n';

    // 打开(置1)第 0、3、5 位
    flags |= (1u << 0);
    flags |= (1u << 3);
    flags |= (1u << 5);
    std::cout << "置1 第0,3,5位 -> "; print_bits8(flags); std::cout << '\n'; // 0010'1001

    // 测试某位
    std::cout << "测试第3位: " << (((flags >> 3) & 1u) ? "1" : "0") << '\n'; // 1
    std::cout << "测试第4位: " << (((flags >> 4) & 1u) ? "1" : "0") << '\n'; // 0

    // 关闭(清0)第 3 位
    flags &= ~(1u << 3);
    std::cout << "清0 第3位   -> "; print_bits8(flags); std::cout << '\n';   // 0010'0001

    // 翻转第 0 位
    flags ^= (1u << 0);
    std::cout << "翻转第0位  -> "; print_bits8(flags); std::cout << '\n';   // 0010'0000
    flags ^= (1u << 0);
    std::cout << "再翻转第0位-> "; print_bits8(flags); std::cout << '\n';   // 0010'0001

    // --- 异或的小特性：a ^ a == 0；a ^ 0 == a ---
    std::cout << "\n--- 异或特性 ---\n";
    unsigned int m = 0b1100'1010;
    std::cout << "m ^ m = " << (m ^ m) << "  (任何数异或自己为 0)\n";
    std::cout << "m ^ 0 = " << (m ^ 0) << "  (任何数异或 0 为自身)\n";

    // --- 优先级陷阱：& | 低于关系运算符，必须加括号 ---
    std::cout << "\n--- 优先级陷阱 ---\n";
    // 错误写法：if (flags & 1u == 0)  会被解析成 flags & (1u == 0)
    //   → flags & 0 → 恒为 0，逻辑完全错误（编译器通常给警告）
    // 正确写法：if ((flags & 1u) == 0)
    if ((flags & 1u) == 0) {
        std::cout << "flags 的最低位为 0\n";
    } else {
        std::cout << "flags 的最低位为 1\n";
    }

    return 0;
}
