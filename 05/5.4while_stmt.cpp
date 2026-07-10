// ===========================================================================
//  《C++ Primer》5.4 节示例：while 语句
// ---------------------------------------------------------------------------
//  本程序：读取未知数量的整数（直到 EOF），找出其中的最大值。
//
//  要点：
//    1. while 的条件每次循环开始时求值：为真才进入循环体，为假则退出。
//    2. 「在条件中读取」是常见且简洁的写法：
//         while (std::cin >> value)
//       当读取失败（遇到 EOF 或类型不匹配）时，流进入失败态，条件为假，循环结束。
//    3. 循环体内必须改变条件涉及的状态，否则可能死循环（这里每次读取新值）。
//    4. 若用户第一个输入就读失败（如直接 EOF），maxVal 不会被更新，
//       因此初始化时用一个标志位 hasValue 加以保护。
// ===========================================================================
#include <iostream>

int main()
{
    std::cout << "请输入若干整数，按 Ctrl+Z(Windows) 或 Ctrl+D(Unix) 结束：" << std::endl;

    int value = 0;
    int maxVal = 0;                // 记录当前最大值
    bool hasValue = false;         // 是否至少读到一个有效值

    // 条件中读取：每次循环先从 cin 读取一个整数到 value
    // 读取成功返回 istream 引用（转为 bool 为 true），失败则退出循环
    while (std::cin >> value) {
        if (!hasValue) {           // 第一个有效输入：直接记为最大值
            maxVal = value;
            hasValue = true;
        } else if (value > maxVal) {
            maxVal = value;        // 出现更大值则更新
        }
        // 循环体结束后自动回到 while 条件，继续读取下一个值
    }

    if (hasValue) {
        std::cout << "最大值为：" << maxVal << std::endl;
    } else {
        std::cout << "未读到任何有效整数。" << std::endl;
    }

    return 0;
}
