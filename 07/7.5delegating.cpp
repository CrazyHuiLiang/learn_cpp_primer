// ===========================================================================
//  《C++ Primer》7.4 节示例：委托构造（delegating constructor）
// ---------------------------------------------------------------------------
//  要点：
//    - 委托构造：一个构造函数的初始值列表只列「另一个本类构造函数」，
//      把初始化工作「委托」给那个构造函数完成，自己（可选地）再做点补充。
//    - 好处：避免在多个构造函数里重复写相同的初始化逻辑。
//    - 执行顺序：先执行被委托的构造函数体，再回到委托者的函数体。
//
//  本例写一个 Sales_data 的精简版（命名 SalesDataMini），演示：
//    SalesDataMini(const std::string &s) 委托给 SalesDataMini(s, 0, 0.0)。
// ===========================================================================
#include <iostream>
#include <string>

class SalesDataMini
{
public:
    // 「目标构造函数」：承担真正的初始化工作
    SalesDataMini(const std::string &s, unsigned n, double p)
        : bookNo(s), units_sold(n), revenue(n * p) {}

    // 「委托构造」：只指定 ISBN，把册数与单价取 0，委托给上面的构造函数。
    //   注意初始值列表里只有一个同类构造函数 SalesDataMini(s, 0, 0.0)。
    SalesDataMini(const std::string &s) : SalesDataMini(s, 0, 0.0) {}

    // 默认构造：也可以委托，进一步委托给 (s, 0, 0.0)
    SalesDataMini() : SalesDataMini("") {}

    // 默认构造（=default 风格在此类不适用，因为已有自定义构造；
    //   委托构造是替代写法之一。）

    std::string isbn() const { return bookNo; }
    double avg_price() const
    {
        return units_sold ? revenue / units_sold : 0;
    }

    void show() const
    {
        std::cout << bookNo << " " << units_sold << " "
                  << revenue << " " << avg_price() << std::endl;
    }

private:
    std::string bookNo;
    unsigned    units_sold = 0;
    double      revenue = 0.0;
};

int main()
{
    SalesDataMini a("0-201-78345-X", 3, 20.0);  // 直接用目标构造
    SalesDataMini b("0-201-99999-9");           // 委托构造：册数/总额为 0
    SalesDataMini c;                            // 默认构造，再委托一次

    std::cout << "a (目标构造):        "; a.show();
    std::cout << "b (委托给目标构造):  "; b.show();
    std::cout << "c (默认→委托):       "; c.show();

    return 0;
}
