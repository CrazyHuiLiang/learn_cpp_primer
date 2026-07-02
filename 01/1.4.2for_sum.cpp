// ===========================================================================
//  《C++ Primer》1.4.2 节示例：for 语句（求和版）
// ---------------------------------------------------------------------------
//  for (init-statement; condition; expression) statement
//    1) init-statement 只在循环开始前执行一次（这里声明并初始化 val）
//    2) 每次循环前求 condition，为真才进入循环体
//    3) 每次循环体结束后执行 expression（这里 ++val）
//
//  与 1.4.1 的 while 版本相比，for 把「初始化、条件、递增」写在同一行，
//  更紧凑、更易读。两者功能等价。
// ===========================================================================
#include <iostream>

int main()
{
    int sum = 0;
    for (int val = 1; val <= 10; ++val)
        sum += val;              // 循环体只有一条语句，可省略花括号
    std::cout << "Sum of 1 to 10 inclusive is " << sum << std::endl;
    return 0;
}
