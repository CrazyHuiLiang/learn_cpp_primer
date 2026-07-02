#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <iostream>
#include <string>

// ===========================================================================
//  Sales_data 类（《C++ Primer》第 7 章定义）
// ---------------------------------------------------------------------------
//  这是第 1 章 Sales_item 的「自定义类」版本：第 1 章我们靠库提供的
//  Sales_item 体会类的用法，第 7 章则亲手把它实现出来，逐步引入
//    - 数据成员与成员函数
//    - 访问控制（public / private）与封装
//    - this 指针与 const 成员函数
//    - 构造函数（默认构造、构造函数初始值列表、委托构造）
//    - 友元（friend）非成员接口函数
//
//  数据成员：
//    - bookNo      ：ISBN
//    - units_sold  ：售出册数（类内初始值 0）
//    - revenue     ：销售总额 = 册数 × 单价（类内初始值 0.0）
//
//  接口（友元非成员函数）：
//    - read(is, sd)   ：从 is 读入 "ISBN 数量 单价"，写入 sd
//    - print(os, sd)  ：把 sd 输出到 os，格式 "ISBN 数量 总额 平均单价"
//    - add(lhs, rhs)  ：返回一个新对象，是两条记录的累加结果
//
//  成员函数：
//    - isbn()         ：返回 ISBN（const 成员函数）
//    - combine(rhs)   ：把 rhs 累加到 *this，返回 *this（支持链式调用）
//    - avg_price()    ：平均单价（私有辅助函数）
// ===========================================================================
class Sales_data
{
    // 友元：允许下列「非成员」函数访问类的私有数据成员
    friend std::istream &read(std::istream &, Sales_data &);
    friend std::ostream &print(std::ostream &, const Sales_data &);
    friend Sales_data add(const Sales_data &, const Sales_data &);

public:
    // ---- 构造函数（7.1.2 / 7.4）----
    // 默认构造函数：用 =default 显式要求编译器合成默认构造。
    //   之所以要显式写，是因为一旦我们定义了任何构造函数，编译器就不再
    //   自动合成默认构造了（见 7.4 节）。
    Sales_data() = default;

    // 只指定 ISBN：册数与总额取类内初始值（0 / 0.0）
    Sales_data(const std::string &s) : bookNo(s) {}

    // 指定 ISBN、册数、单价：用构造函数初始值列表初始化所有成员
    Sales_data(const std::string &s, unsigned n, double p)
        : bookNo(s), units_sold(n), revenue(n * p) {}

    // 从输入流构造：委托给非成员函数 read 完成读取
    Sales_data(std::istream &is) { read(is, *this); }

    // ---- 成员函数 ----
    // 返回 ISBN。const 修饰说明 this 指向 const，即该函数不修改对象。
    std::string isbn() const { return bookNo; }

    // 把 rhs 累加到当前对象，返回 *this 以支持链式调用。
    Sales_data &combine(const Sales_data &);

    // 平均单价；units_sold 为 0 时返回 0（避免除零）。
    double avg_price() const;

private:
    // 私有数据成员：外部不可直接访问，只能通过成员函数/友元操作。
    std::string bookNo;            // ISBN
    unsigned    units_sold = 0;    // 售出册数（类内初始值）
    double      revenue = 0.0;     // 销售总额（类内初始值）
};

// ---------------------------------------------------------------------------
//  成员函数实现（inline 风格，写在头文件内，与 Sales_item.h 保持一致）
// ---------------------------------------------------------------------------

// combine：累加册数与总额，返回 *this
inline Sales_data &Sales_data::combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;  // 累加册数
    revenue    += rhs.revenue;     // 累加总额
    return *this;                  // 返回引用，支持 a.combine(b).combine(c)
}

// avg_price：平均单价
inline double Sales_data::avg_price() const
{
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;                  // 册数为 0 时返回 0，避免除零
}

// ---------------------------------------------------------------------------
//  友元非成员函数实现
// ---------------------------------------------------------------------------

// read：从流中读取 "ISBN 数量 单价"
//   读取失败时应将对象置为默认状态（与 Sales_item.h 的处理一致）。
inline std::istream &read(std::istream &is, Sales_data &item)
{
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    if (is)                        // 仅当读取成功才计算总额
        item.revenue = item.units_sold * price;
    else
        item = Sales_data();       // 读取失败：重置为默认状态
    return is;
}

// print：输出 "ISBN 数量 总额 平均单价"
//   注意不输出换行，让调用者决定是否换行（与标准库风格一致）。
inline std::ostream &print(std::ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

// add：返回一个新对象，是两条记录的累加结果
//   用「拷贝 lhs + combine(rhs)」实现，复用 combine。
inline Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;          // 拷贝 lhs
    sum.combine(rhs);              // 复用 combine
    return sum;                    // 返回新对象
}

#endif // SALES_DATA_H
