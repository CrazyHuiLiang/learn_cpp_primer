// ===========================================================================
//  《C++ Primer》7.1 节示例：使用 Sales_data 类（基础）
// ---------------------------------------------------------------------------
//  功能：从标准输入读入一条销售记录，用友元函数 print 输出。
//
//  要点：
//    - Sales_data 是我们在第 7 章自定义的类（见 include/Sales_data.h）。
//    - read / print 是「非成员」的友元函数，用法与运算符 >> / << 类似，
//      但这里以函数调用形式出现：read(std::cin, item)。
//    - 与第 1 章相比，我们不再依赖库提供的 Sales_item，而是亲手实现类。
//
//  输入示例：
//    0-201-78345-X 3 20.00
//  输出：
//    0-201-78345-X 3 60 20
// ===========================================================================
#include <iostream>
#include "Sales_data.h"

int main()
{
    Sales_data item;               // 默认构造：bookNo 空, units_sold=0, revenue=0.0

    std::cout << "请输入一条销售记录（ISBN 数量 单价）：" << std::endl;
    read(std::cin, item);          // 友元函数：读入一条记录到 item

    std::cout << "ISBN 册数 总额 平均单价：" << std::endl;
    print(std::cout, item) << std::endl;  // 友元函数：输出 item

    return 0;
}
