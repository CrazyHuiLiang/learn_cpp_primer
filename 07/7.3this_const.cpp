// ===========================================================================
//  《C++ Primer》7.3 节示例：this 指针与 const 成员函数
// ---------------------------------------------------------------------------
//  要点：
//    - 每个非静态成员函数都有一个隐式形参 this，指向调用该函数的对象。
//    - isbn() 是「const 成员函数」：其 this 指向「const Sales_data*」，
//      即承诺不修改对象。const 对象只能调用 const 成员函数。
//    - combine() 返回 *this（Sales_data&），因此可以链式调用：
//         item.combine(a).combine(b);   // 等价于 item.combine(a); item.combine(b);
//    - 非 const 成员函数的 this 指向「非 const Sales_data*」，因此不能
//      在 const 对象上调用。下面用代码演示这一限制。
// ===========================================================================
#include <iostream>
#include "Sales_data.h"

int main()
{
    Sales_data item("0-201-78345-X", 3, 20.0);   // 非常量对象
    Sales_data a("0-201-78345-X", 2, 25.0);
    Sales_data b("0-201-78345-X", 1, 10.0);

    // ---- this 指针与链式调用 ----
    // combine 返回 *this（即 item 的引用），所以可以再 .combine(b)。
    // 整条语句相当于：item.combine(a); item.combine(b);
    item.combine(a).combine(b);
    print(std::cout, item) << std::endl;   // 3+2+1=6 册, 60+50+10=120 总额

    // ---- const 成员函数 ----
    // isbn() 后面的 const 表示「this 指向 const」，不修改对象。
    std::cout << "ISBN: " << item.isbn() << std::endl;

    // ---- const 对象只能调用 const 成员函数 ----
    const Sales_data const_item("0-201-78346-X", 5, 10.0);

    // 合法：isbn() 是 const 成员函数，const 对象可调用
    std::cout << "const 对象的 ISBN: " << const_item.isbn() << std::endl;

    // 合法：read/print/add 是非成员函数（无 this），不在此限制内
    //   print 的第二个参数是 const Sales_data&，const 对象可绑定。
    print(std::cout, const_item) << std::endl;

    // 非法：combine 是非 const 成员函数（会修改对象），const 对象不能调用。
    //   取消下面注释，编译器会报类似 "object has type qualifiers that are
    //   incompatible with member function" 的错误。
    // const_item.combine(a);   // 错误���combine 不是 const 成员函数

    return 0;
}
