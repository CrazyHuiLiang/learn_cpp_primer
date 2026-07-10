// ===========================================================================
//  《C++ Primer》4.2 节示例：逻辑运算符与关系运算符
// ---------------------------------------------------------------------------
//  要点：
//    1. 关系运算符：< <= > >= == !=  （结果为 bool）
//    2. 逻辑运算符：&&（与）、||（或）、!（非）
//    3. 短路求值(short-circuit)：
//       - && : 若左侧为 false，则整个表达式必为 false，右侧不求值。
//       - || : 若左侧为 true ，则整个表达式必为 true ，右侧不求值。
//       这意味着右侧可以依赖左侧的检查结果（如先判空再解引用）。
//    4. 关系运算符不要连写：a < b < c 会被解释为 (a<b) < c（bool 转 int），
//       应写成 a < b && b < c。
//    5. 建议：比较结果应作为条件使用，不要把 == 误写成 =。
// ===========================================================================
#include <iostream>
#include <vector>

// 一个「有副作用」的函数：被调用时打印一行，用来观察是否被求值
bool check(int v)
{
    std::cout << "    [check] 被调用，参数 v=" << v << '\n';
    return v > 0;
}

int main()
{
    // --- 关系运算符 ---
    int a = 3, b = 7;
    std::cout << "a=" << a << ", b=" << b << '\n';
    std::cout << "a <  b ? " << (a <  b) << '\n';   // 1 (true)
    std::cout << "a <= b ? " << (a <= b) << '\n';   // 1
    std::cout << "a >  b ? " << (a >  b) << '\n';   // 0 (false)
    std::cout << "a >= b ? " << (a >= b) << '\n';   // 0
    std::cout << "a == b ? " << (a == b) << '\n';   // 0
    std::cout << "a != b ? " << (a != b) << '\n';   // 1

    // --- 逻辑运算符 ---
    std::cout << "\n--- 逻辑运算符 ---\n";
    bool t = true, f = false;
    std::cout << "t && f = " << (t && f) << '\n';   // 0
    std::cout << "t || f = " << (t || f) << '\n';   // 1
    std::cout << "!f     = " << (!f)     << '\n';   // 1
    std::cout << "!t     = " << (!t)     << '\n';   // 0

    // --- 短路求值：&& 左侧为假则不评估右侧 ---
    std::cout << "\n--- 短路求值：&& ---\n";
    std::cout << "case1: false && check(100)\n";
    if (false && check(100)) {                      // 左侧为 false → 右侧不求值
        std::cout << "  成立\n";
    } else {
        std::cout << "  不成立（注意上面没有打印 [check]）\n";
    }

    std::cout << "case2: true && check(100)\n";
    if (true && check(100)) {                       // 左侧为 true → 必须求值右侧
        std::cout << "  成立\n";
    }

    // --- 短路求值：|| 左侧为真则不评估右侧 ---
    std::cout << "\n--- 短路求值：|| ---\n";
    std::cout << "case3: true || check(-5)\n";
    if (true || check(-5)) {                        // 左侧为 true → 右侧不求值
        std::cout << "  成立（注意上面没有打印 [check]）\n";
    }

    std::cout << "case4: false || check(-5)\n";
    if (false || check(-5)) {                       // 左侧为 false → 必须求值右侧
        std::cout << "  成立\n";
    } else {
        std::cout << "  不成立（check 返回 false）\n";
    }

    // --- 实用场景：先判空再访问，避免解引用空指针/越界 ---
    std::cout << "\n--- 实用场景：安全访问 ---\n";
    std::vector<int> vec;
    // 若 vec 为空，则 && 短路，不会去访问 vec[0]（否则越界 UB）
    if (!vec.empty() && vec[0] > 0) {
        std::cout << "  第一个元素为正\n";
    } else {
        std::cout << "  容器为空（短路保护了 vec[0] 的访问）\n";
    }

    // --- 常见错误：关系运算符连写 ---
    std::cout << "\n--- 关系运算符不要连写 ---\n";
    int x = 5;
    // 错误写法：1 < x < 3  →  (1 < x) < 3  →  true < 3  →  1 < 3  →  true
    // 虽然「恰好」结果对，但语义完全错误（bool 隐式转 int 参与 < 比较）
    // 编译器通常会给 -Wparentheses / -Wbool-compare 警告，提示「不像数学含义」。
    // 下面这行是「反面教材」，故用 pragma 临时关闭这两个警告，方便观察其行为：
#if defined(__GNUC__) && !defined(__clang__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wparentheses"
#  pragma GCC diagnostic ignored "-Wbool-compare"
#endif
    bool wrong = 1 < x < 3;        // 等价于 (1 < x) < 3，即 bool(true) < 3
#if defined(__GNUC__) && !defined(__clang__)
#  pragma GCC diagnostic pop
#endif
    std::cout << "  (错误写法) 1 < x < 3 = " << wrong << "   <- 被误判为真！\n";
    // 正确写法：用 && 串联两个关系
    bool correct = (1 < x) && (x < 3);
    std::cout << "  (正确写法) 1 < x && x < 3 = " << correct << '\n'; // 0

    return 0;
}
