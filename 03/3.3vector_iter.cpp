// ===========================================================================
//  《C++ Primer》3.4 节示例：vector 迭代器
// ---------------------------------------------------------------------------
//  迭代器(iterator) 类似指针，用于访问容器中的元素。
//    - v.begin()  指向第一个元素的迭代器
//    - v.end()    指向「尾后位置(last one past)」的迭代器（不存在的元素）
//    - *it        解引用：得到 it 指向的元素
//    - ++it       前进一步，指向下一个元素
//    - it != v.end()  是判断是否遍历完的标准写法
//
//  迭代器算术：
//    - it + n / it - n      前进/后退 n 步
//    - it2 - it1            两个迭代器的距离，类型为 difference_type（有符号）
//    - 比较运算符 <, >, <=, >=  判断先后顺序
//
//  本程序：
//    1. 用迭代器遍历并打印 vector
//    2. 用迭代器修改每个元素（*it = ...）
//    3. 演示迭代器算术与 difference_type
// ===========================================================================
#include <iostream>
#include <vector>
#include <iterator>      // std::distance 也可用，但这里主要讲内置算术

int main()
{
    std::vector<int> v = {10, 20, 30, 40, 50};

    // ---- 1. 用迭代器遍历 ----
    // auto 让编译器推断迭代器类型（std::vector<int>::iterator）
    std::cout << "用迭代器遍历：";
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << ' ';          // *it 解引用得到当前元素
    }
    std::cout << "\n";

    // ---- 2. 用迭代器修改元素 ----
    // *it 返回元素的引用，对其赋值即修改原元素
    for (auto it = v.begin(); it != v.end(); ++it) {
        *it *= 2;                          // 每个元素翻倍
    }
    std::cout << "翻倍后：";
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << "\n";                     // 20 40 60 80 100

    // ---- 3. 迭代器算术 ----
    auto mid = v.begin() + v.size() / 2;   // 指向「中间」元素的迭代器
    std::cout << "中间元素 = " << *mid << "\n";   // 60

    // it2 - it1 的类型是 difference_type（有符号整数类型）
    // 这里 mid - v.begin() 得到中间元素的下标
    std::vector<int>::difference_type diff = mid - v.begin();
    std::cout << "mid 距离 begin 的步数 = " << diff << "\n";   // 2

    // 也可以直接让两个迭代器相减
    auto last = v.end() - 1;               // 指向最后一个元素
    std::cout << "最后一个元素 = " << *last << "\n";            // 100
    std::cout << "last - begin = " << (last - v.begin()) << "\n"; // 4

    // ---- 4. cbegin/cend：得到 const 迭代器（只读，不能修改元素）----
    std::cout << "用 const 迭代器只读遍历：";
    for (auto it = v.cbegin(); it != v.cend(); ++it) {
        std::cout << *it << ' ';
        // *it = 0;  // 编译错误：const 迭代器指向的是常量，不可修改
    }
    std::cout << "\n";

    return 0;
}
