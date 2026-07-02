#ifndef SALES_ITEM_H
#define SALES_ITEM_H

#include <iostream>
#include <string>

// ===========================================================================
//  Sales_item 类（《C++ Primer》第 1 章 1.5 节引入）
// ---------------------------------------------------------------------------
//  表示一条销售记录，包含三个数据成员：
//    - bookNo      ：书的 ISBN 号
//    - units_sold  ：售出册数
//    - revenue     ：销售总额（册数 × 单价）
//
//  该类对外提供的能力（都是通过「运算符重载」实现的，第 14 章会详细讲解）：
//    - 读取：  std::cin >> item;        （读入格式：ISBN 数量 单价）
//    - 输出：  std::cout << item;       （输出格式：ISBN 数量 总额 平均单价）
//    - 相加：  item1 + item2;           （要求两者 ISBN 相同）
//    - 累加：  item1 += item2;
//    - 比较：  item1 == item2 / item1 != item2
//    - 取 ISBN：item.isbn()             （成员函数，1.5.2 节演示）
//
//  这里只给出实现以便第 1 章的示例能直接编译运行；
//  类的完整设计思路在第 7 章（类）、第 14 章（运算符重载）才会展开。
// ===========================================================================
class Sales_item
{
    // 友元（friend）：允许下列「非成员」运算符访问类的私有数据成员
    friend std::istream &operator>>(std::istream &, Sales_item &);
    friend std::ostream &operator<<(std::ostream &, const Sales_item &);
    friend bool operator==(const Sales_item &, const Sales_item &);
    friend bool operator!=(const Sales_item &, const Sales_item &);

public:
    // 默认构造函数：使用类内初始值（units_sold=0, revenue=0.0）
    Sales_item() = default;

    // 只指定 ISBN 的构造
    Sales_item(const std::string &book) : bookNo(book) {}

    // 指定 ISBN、数量、单价的构造
    Sales_item(const std::string &book, unsigned cnt, double price)
        : bookNo(book), units_sold(cnt), revenue(cnt * price) {}

    // 从输入流构造：读取一条记录
    Sales_item(std::istream &is) { is >> *this; }

    // 成员函数：返回 ISBN
    std::string isbn() const { return bookNo; }

    // 复合赋值运算符：把 rhs 累加到当前对象
    Sales_item &operator+=(const Sales_item &);

private:
    std::string bookNo;        // ISBN
    unsigned    units_sold = 0; // 售出册数
    double      revenue = 0.0;  // 销售总额

    // 平均单价：私有辅助函数，供输出运算符使用
    double avg_price() const
    {
        if (units_sold)
            return revenue / units_sold;
        else
            return 0;
    }
};

// 输入运算符：从流中读取 "ISBN 数量 单价"
inline std::istream &operator>>(std::istream &in, Sales_item &s)
{
    double price;
    in >> s.bookNo >> s.units_sold >> price;
    if (in)                       // 仅当读取成功才计算总额
        s.revenue = s.units_sold * price;
    else
        s = Sales_item();         // 读取失败则重置为空记录
    return in;
}

// 输出运算符：依次输出 ISBN 数量 总额 平均单价
inline std::ostream &operator<<(std::ostream &out, const Sales_item &s)
{
    out << s.isbn() << " " << s.units_sold << " "
        << s.revenue << " " << s.avg_price();
    return out;
}

// 相等：ISBN、册数、总额三者都相同
inline bool operator==(const Sales_item &lhs, const Sales_item &rhs)
{
    return lhs.isbn() == rhs.isbn() &&
           lhs.units_sold == rhs.units_sold &&
           lhs.revenue == rhs.revenue;
}

inline bool operator!=(const Sales_item &lhs, const Sales_item &rhs)
{
    return !(lhs == rhs);
}

// 复合赋值：累加册数与总额
inline Sales_item &Sales_item::operator+=(const Sales_item &rhs)
{
    units_sold += rhs.units_sold;
    revenue    += rhs.revenue;
    return *this;
}

// 加法：用「拷贝 + 复合赋值」实现，复用 operator+=
inline Sales_item operator+(const Sales_item &lhs, const Sales_item &rhs)
{
    Sales_item sum = lhs;   // 拷贝 lhs
    sum += rhs;             // 复用 operator+=
    return sum;
}

#endif // SALES_ITEM_H
