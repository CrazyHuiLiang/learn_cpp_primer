// ===========================================================================
//  《C++ Primer》3.4 节经典示例：用迭代器实现二分查找
// ---------------------------------------------------------------------------
//  在「有序」序列中查找目标值，二分查找是经典算法。
//  书中用迭代器实现，突出迭代器的算术运算：
//      mid = beg + (end - beg) / 2
//
//  为什么是 (end - beg) / 2，而不是 (beg + end) / 2？
//    - 两个迭代器【不能相加】（beg + end 非法）！
//    - 但「迭代器 - 迭代器」合法，结果是 difference_type（有符号整数）；
//      再用「迭代器 + 整数」得到中间迭代器。
//    - 这同时避免了整数溢出问题（虽然这里影响不大，但它是好习惯）。
//
//  约定：
//    - beg 指向待查区间第一个元素；
//    - end 指向「尾后」位置（待查区间为 [beg, end)）；
//    - 每次根据 *mid 与 target 的比较，把区间折半。
//
//  本程序：在有序 vector<int> 中查找目标值，输出是否找到及位置（下标）。
// ===========================================================================
#include <iostream>
#include <vector>

int main()
{
    // 必须是有序序列，二分查找才有意义
    std::vector<int> text = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

    std::cout << "有序序列：";
    for (auto x : text) std::cout << x << ' ';
    std::cout << "\n请输入要查找的整数：";

    int sought = 0;
    if (!(std::cin >> sought)) {
        std::cerr << "输入无效\n";
        return 1;
    }

    // ---- 二分查找 ----
    auto beg = text.begin();          // 区间起点
    auto end = text.end();            // 区间尾后位置（不指向任何元素）
    auto orig_begin = beg;            // 记住起点，用于最后换算下标
    bool found = false;

    while (beg != end) {              // 区间非空才继续查找
        auto mid = beg + (end - beg) / 2;   // 中间迭代器

        if (*mid == sought) {         // 找到目标
            std::cout << "找到 " << sought
                      << "，下标为 " << (mid - orig_begin) << std::endl;
            found = true;
            break;
        } else if (*mid < sought) {   // 目标在右半边
            beg = mid + 1;
        } else {                      // 目标在左半边
            end = mid;
        }
    }

    if (!found) {
        std::cout << "未找到 " << sought << std::endl;
    }

    return 0;
}
