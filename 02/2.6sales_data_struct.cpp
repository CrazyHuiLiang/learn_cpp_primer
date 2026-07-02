// ===========================================================================
//  《C++ Primer》2.6 节示例：自定义 Sales_data 结构体（第 2 章版本）
// ---------------------------------------------------------------------------
//  要点：
//    1. struct 定义：「类内初始值(in-class initializer)」（C++11）让数据成员
//       在创建对象时就有确定的初值，避免函数体内默认初始化的不确定值。
//    2. 本程序实现一个最简单的「书店累加」逻辑（与第 1 章综合示例呼应，
//       但这里我们直接操作 struct 成员，不用 Sales_item 类）：
//         - 从 cin 读入若干条交易（ISBN 数量 单价）；
//         - 假设输入按 ISBN 排序，把「同一 ISBN 且连续出现」的交易累加成
//           一条汇总记录后输出；遇到新 ISBN 时输出上一组并开始新累加。
//    3. 体现第 2 章要点：struct 定义、类内初始值、std::string 与基本类型的
//       混合使用、用 . 访问成员。
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
#include <string>

// 第 2 章版本的 Sales_data：仅数据成员，无任何成员函数/运算符重载。
// 类内初始值保证「默认创建的对象」有确定的初值（units_sold=0, revenue=0.0）。
struct Sales_data {
    std::string bookNo;           // ISBN
    unsigned    units_sold = 0;   // 售出册数（类内初始值）
    double      revenue    = 0.0; // 销售总额（类内初始值）
};

int main()
{
    Sales_data total;             // 当前正在累加的汇总记录
    // total.bookNo 为空串, total.units_sold=0, total.revenue=0.0（类内初始值）

    // 读入第一条交易；若有数据才进入处理
    double price = 0.0;
    if (std::cin >> total.bookNo >> total.units_sold >> price) {
        total.revenue = total.units_sold * price;

        Sales_data trans;         // 逐笔读入的临时记录
        while (std::cin >> trans.bookNo >> trans.units_sold >> price) {
            trans.revenue = trans.units_sold * price;

            if (total.bookNo == trans.bookNo) {
                // 同一 ISBN：把 trans 累加到 total
                total.units_sold += trans.units_sold;
                total.revenue    += trans.revenue;
            } else {
                // 换书：先输出上一组汇总
                std::cout << total.bookNo << " "
                          << total.units_sold << " "
                          << total.revenue << " ";
                if (total.units_sold != 0)
                    std::cout << total.revenue / total.units_sold;
                else
                    std::cout << 0;
                std::cout << "\n";

                // 开始累加新的一组
                total = trans;
            }
        }
        // 循环结束后，最后一组还没输出
        std::cout << total.bookNo << " "
                  << total.units_sold << " "
                  << total.revenue << " ";
        if (total.units_sold != 0)
            std::cout << total.revenue / total.units_sold;
        else
            std::cout << 0;
        std::cout << "\n";
    } else {
        std::cerr << "No data?!" << std::endl;   // 没有任何输入
        return -1;
    }

    return 0;
}
