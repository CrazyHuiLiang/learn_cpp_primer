// ===========================================================================
//  《C++ Primer》7.1 节示例：读入两条记录，ISBN 相同则累加
// ---------------------------------------------------------------------------
//  功能：从标准输入读入两条销售记录：
//    - 若 ISBN 相同，用 combine 累加并输出；
//    - 否则在标准错误上提示，并返回非 0 表示失败。
//
//  要点：
//    - item1.combine(item2) 把 item2 累加到 item1，返回 item1 的引用。
//    - 这里用成员函数 isbn() 比较 ISBN（成员函数的调用方式）。
//    - 与 1.5.2sales_member.cpp 对照：那里用 Sales_item + operator+，
//      这里用自定义的 Sales_data + combine，体会第 7 章的实现思路。
//
//  输入示例（ISBN 相同 → 累加）：
//    0-201-78345-X 3 20.00
//    0-201-78345-X 2 25.00
//  输出：
//    0-201-78345-X 5 110 22
// ===========================================================================
#include <iostream>
#include "Sales_data.h"

int main()
{
    Sales_data item1, item2;

    std::cout << "请��入两条销售记录（每行：ISBN 数量 单价）：" << std::endl;
    read(std::cin, item1);
    read(std::cin, item2);

    // 用成员函数 isbn() 比较 ISBN
    if (item1.isbn() == item2.isbn()) {
        item1.combine(item2);              // 把 item2 累加到 item1
        print(std::cout, item1) << std::endl;
        return 0;                          // 正常结束
    } else {
        std::cerr << "Data must refer to same ISBN" << std::endl;
        return -1;                         // 异常结束
    }
}
