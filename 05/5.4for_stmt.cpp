// ===========================================================================
//  《C++ Primer》5.4 节示例：传统 for 与范围 for 对比
// ---------------------------------------------------------------------------
//  本程序：
//    1. 用传统 for 求 1~N 的整数和；
//    2. 用范围 for 遍历 vector，并以 auto& 引用方式原地修改元素（每个元素 *2）。
//
//  要点：
//    1. 传统 for 形式：for (init; condition; expression) { ... }
//         - init 只在进入循环时执行一次
//         - condition 每次循环开始求值，为真才进入循环体
//         - expression 每次循环体结束后执行
//    2. 范围 for 形式：for (declaration : range) { ... }
//         - declaration 通常用 auto 或 const auto&（只读）/ auto&（可改）
//         - 范围 for 实际上等价于用迭代器遍历的传统 for，编译器会展开为：
//               for (auto it = range.begin(); it != range.end(); ++it) {
//                   declaration = *it;
//                   ...
//               }
//         - 因此「遍历过程中不能改变容器大小」（如 push_back/erase），
//           否则可能使迭代器失效，导致未定义行为。
// ===========================================================================
#include <iostream>
#include <vector>

int main()
{
    // ---------- 1. 传统 for 求和 ----------
    const int N = 10;
    int sum = 0;
    for (int i = 1; i <= N; ++i) { // init: i=1; condition: i<=N; expression: ++i
        sum += i;
    }
    std::cout << "1 到 " << N << " 的和 = " << sum << std::endl;

    // ---------- 2. 范围 for 遍历 vector ----------
    std::vector<int> nums = {1, 2, 3, 4, 5};

    // 只读遍历：用 const auto& 避免拷贝
    std::cout << "原 vector: ";
    for (const auto &x : nums) {   // 范围 for：对每个元素 x（只读引用）
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    // 修改元素：必须用 auto&（引用），否则改的是副本
    // 若写成 for (auto x : nums)，则 x 是每个元素的拷贝，修改不影响原元素
    for (auto &x : nums) {         // auto& 引用：可原地修改容器内元素
        x *= 2;
    }
    // 注意：遍历过程中不能调用 push_back/erase 等改变 nums 大小��操作，
    // 否则迭代器可能失效，引发未定义行为。

    std::cout << "翻倍后  : ";
    for (const auto &x : nums) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    // 上面范围 for 等价于下面这段传统 for（编译器展开形式）：
    //   for (auto it = nums.begin(); it != nums.end(); ++it) {
    //       auto &x = *it;
    //       x *= 2;
    //   }

    return 0;
}
