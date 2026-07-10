// ===========================================================================
//  《C++ Primer》7.1 节示例：书店程序（第 7 章版本）
// ---------------------------------------------------------------------------
//  场景：书店有每笔交易的记录（ISBN 数量 单价）。需要把「同一 ISBN 且
//       连续出现」的多笔交易累加成一条汇总记录后输出；一旦遇到新的
//       ISBN，就把上一组汇总输出，再开始累加新的一组。
//
//  这是 1.6bookstore.cpp 的第 7 章重写版：把 Sales_item + operator>>/<<
//  换成自定义的 Sales_data + read/print/combine，逻辑完全对应：
//    1. 读入第一条记录到 total（当前正在累加的汇总）。
//    2. 逐条读入 trans：
//         - 若 trans 与 total 同 ISBN → total.combine(trans)；
//         - 否则 → print 输出 total，让 total = trans（开始新一组）。
//    3. 循环结束后，最后一组 total 还没输出，补上。
//
//  输入示例：
//    0-201-78345-X 3 20.00
//    0-201-78345-X 2 25.00
//    0-201-78346-X 1 10.00
//    0-201-78346-X 4 10.00
//  输出：
//    0-201-78345-X 5 110 22
//    0-201-78346-X 5 50 10
// ===========================================================================
#include <iostream>
#include "Sales_data.h"

int main()
{
    Sales_data total;              // 当前正在累加的汇总记录

    std::cout << "请输入交易记录（每行：ISBN 数量 单价），Ctrl+Z 结束：" << std::endl;
    // 读入第一条记录；若有数据才进入处理
    if (read(std::cin, total)) {
        Sales_data trans;          // 逐笔读入的记录
        while (read(std::cin, trans)) {
            if (total.isbn() == trans.isbn()) {
                total.combine(trans);    // 同一本书：累加
            } else {
                print(std::cout, total) << std::endl;  // 换书：输出上一组
                total = trans;                          // 开始新一组
            }
        }
        // 输出最后一组（循环结束时仍未输出）
        print(std::cout, total) << std::endl;
    } else {
        std::cerr << "No data?!" << std::endl;     // 没有任何输入
        return -1;
    }

    return 0;
}
