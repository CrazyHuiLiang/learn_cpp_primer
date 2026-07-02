// ===========================================================================
//  《C++ Primer》1.4.4 节示例：if 语句 —— 统计连续重复值
// ---------------------------------------------------------------------------
//  功能：读入一串整数，统计每个值「连续」出现的次数。
//  例如输入： 42 42 42 42 55 55 62 100 100 100
//    输出：
//      42 occurs 4 times
//      55 occurs 2 times
//      62 occurs 1 times
//      100 occurs 3 times
//
//  思路：
//    - currVal 保存当前正在统计的值，cnt 统计它连续出现的次数。
//    - 读到一个与 currVal 相同的值 → cnt++；
//    - 读到一个不同的值 → 先输出上一组的统计结果，再开始统计新值。
//    - 最后还要补输出最后一组（循环结束后）。
//
//  调试建议：在 if (val == currVal) 处下断点，观察 currVal 与 cnt 的变化。
// ===========================================================================
#include <iostream>

int main()
{
    int currVal = 0, val = 0;

    // 先读入第一个数，作为初始的 currVal；若没有任何输入则直接结束
    if (std::cin >> currVal) {
        int cnt = 1;                  // currVal 已出现 1 次
        while (std::cin >> val) {     // 继续读后续数据
            if (val == currVal)       // 与当前值相同
                ++cnt;
            else {                    // 遇到一个新值
                std::cout << currVal << " occurs "
                          << cnt << " times" << std::endl;
                currVal = val;        // 切换到新值
                cnt = 1;              // 重置计数
            }
        }
        // 循环结束时，最后一组还没有输出，这里补上
        std::cout << currVal << " occurs "
                  << cnt << " times" << std::endl;
    }

    return 0;
}
