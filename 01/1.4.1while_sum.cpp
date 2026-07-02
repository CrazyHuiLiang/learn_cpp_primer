// ===========================================================================
//  《C++ Primer》1.4.1 节示例：while 语句
// ---------------------------------------------------------------------------
//  while (condition) statement
//    - 只要 condition 为真，就反复执行 statement。
//    - 本程序利用 while 求 1 到 10 的整数之和。
//
//  调试建议：在 sum += val; 处下断点，观察 sum 与 val 如何逐步变化。
// ===========================================================================
#include <iostream>

int main()
{
    int sum = 0, val = 1;         // sum 累加结果，val 当前待加的数
    while (val <= 10) {
        sum += val;               // 等价于 sum = sum + val
        ++val;                    // 等价于 val = val + 1
    }
    std::cout << "Sum of 1 to 10 inclusive is " << sum << std::endl;
    return 0;
}
