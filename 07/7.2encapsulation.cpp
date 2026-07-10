// ===========================================================================
//  《C++ Primer》7.2 节示例：访问控制与封装
// ---------------------------------------------------------------------------
//  要点：
//    - 用 public / private 控制访问权限：
//        * public  ：类的外部接口，外部代码可访问。
//        * private ：内部实现细节，外部不可直接访问，只能通过成员函数。
//    - 封装的好处：内部实现可变，接口稳定。例如 Sales_data 内部把
//      revenue 改成「册数 × 单价」实时计算，外部用 print/read 的代码
//      完全不用改；只要 isbn()/combine() 等接口不变，使用者无感知。
//    - 外部不能直接访问 private 成员：下面演示对 revenue 的直接访问
//      会被编译器拒绝（注释掉的代码即非法）。
//
//  本例同时定义一个简单 Account 类演示封装：外部不能直接改 balance，
//      只能通过 deposit/withdraw 操作，从而保证余额不会被随意篡改。
// ===========================================================================
#include <iostream>
#include <string>
#include "Sales_data.h"

// ---- 简单的 Account 类：演示封装 ----
class Account
{
public:
    Account() = default;
    Account(const std::string &owner, double bal) : owner_(owner), balance_(bal) {}

    // 只读访问器：外部可读不可写
    const std::string &owner()    const { return owner_; }
    double             balance()  const { return balance_; }

    // 存款：增加余额
    void deposit(double amt) { if (amt > 0) balance_ += amt; }

    // 取款：金额不足则失败，返回是否成功
    bool withdraw(double amt)
    {
        if (amt <= 0 || amt > balance_) return false;  // 金额非法或不足
        balance_ -= amt;
        return true;
    }

private:
    std::string owner_;            // 户主
    double      balance_ = 0.0;    // 余额（封装起来，外部只能通过成员函数操作）
};

int main()
{
    // ---- 用 Sales_data 演示封装 ----
    Sales_data item("0-201-78345-X", 3, 20.0);   // 用构造函数初始化

    // 合法：isbn() 是 public 成员函数
    std::cout << "ISBN: " << item.isbn() << std::endl;

    // 合法：combine / avg_price(通过 print) 都是 public 接口
    Sales_data more("0-201-78345-X", 2, 25.0);
    item.combine(more);
    print(std::cout, item) << std::endl;

    // 非法：revenue / units_sold 是 private，外部不可直接访问。
    //   取消下面任一行注释，编译器会报类似 "private member" 的错误。
    // std::cout << item.revenue;      // 错误：revenue 是 private
    // item.units_sold = 100;          // 错误：units_sold 是 private

    // ---- 用 Account 演示封装：余额只能通过 deposit/withdraw 改变 ----
    Account acc("Alice", 100.0);
    std::cout << "\n" << acc.owner() << " 余额: " << acc.balance() << std::endl;

    acc.deposit(50.0);             // 存 50
    std::cout << "存入 50 后余额: " << acc.balance() << std::endl;

    if (acc.withdraw(30.0))        // 取 30
        std::cout << "取出 30 后余额: " << acc.balance() << std::endl;

    if (!acc.withdraw(1000.0))     // 余额不足，取款失败
        std::cout << "取款 1000 失败（余额不足），余额仍为: "
                  << acc.balance() << std::endl;

    // acc.balance_ = 1e9;          // 错误：balance_ 是 private，无法直接篡改

    return 0;
}
