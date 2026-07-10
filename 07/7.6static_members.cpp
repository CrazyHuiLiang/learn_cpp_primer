// ===========================================================================
//  《C++ Primer》7.6 节示例：类的静态成员（static members）
// ---------------------------------------------------------------------------
//  要点：
//    - static 数据成员属于「类」而非每个对象，所有对象共享同一份。
//    - static 成员函数没有 this 指针，因此：
//        * 不能声明为 const（const 是修饰 this 的，没有 this 自然不能用）；
//        * 只能访问类的 static 成员，不能直接访问非 static 成员。
//    - static 数据成员的「定义」通常放在类外（一处），C++17 起对 inline
//      变量也可在类内定义；这里采用传统的「类内声明 + 类外定义」写法。
//
//  本例用 Account 类演示：
//    - static 成员 rate 记录利率（所有账户共享）；
//    - static 成员 count 统计已创建的对象个数；
//    - static 成员函数 get_rate / get_count 访问 static 成员。
// ===========================================================================
#include <iostream>
#include <string>

class Account
{
public:
    Account(const std::string &owner, double bal)
        : owner_(owner), balance_(bal)
    {
        ++count_;               // 每创建一个对象，静态计数 +1
    }

    // 静态成员函数：没有 this，不能声明为 const
    static double get_rate()        { return rate_; }
    static void   set_rate(double r){ rate_ = r; }
    static std::size_t get_count()  { return count_; }

    // 普通成员函数：可以访问 static 与非 static 成员
    void deposit(double amt) { if (amt > 0) balance_ += amt; }
    double interest() const  { return balance_ * rate_; }  // 用 static rate_ 计算
    const std::string &owner() const { return owner_; }
    double balance() const { return balance_; }

private:
    std::string owner_;
    double      balance_ = 0.0;

    // 静态数据成员：类内「声明」（static 关键字），类外「定义」
    static double   rate_;        // 利率：所有账户共享
    static std::size_t count_;    // 已创建的对象个数
};

// 静态数据成员的类外定义（不再写 static，但要带类型与类名限定）
double      Account::rate_  = 0.05;   // 初始利率 5%
std::size_t Account::count_ = 0;      // 初始计数 0

int main()
{
    std::cout << "初始利率: " << Account::get_rate() << std::endl;  // 用类名调用
    std::cout << "已创建账户数: " << Account::get_count() << std::endl;

    Account a1("Alice", 1000.0);
    Account a2("Bob",   2000.0);
    Account a3("Carol", 500.0);

    // count_ 被三个对象共享，每构造一次 +1
    std::cout << "\n创建 3 个账户后：" << std::endl;
    std::cout << "已创建账户数: " << Account::get_count() << std::endl;

    // rate_ 也是共享的：改一次，所有账户的利息计算都受影响
    Account::set_rate(0.03);      // 调整为 3%
    std::cout << "\n调整利率为 0.03 后：" << std::endl;
    std::cout << a1.owner() << " 利息: " << a1.interest() << std::endl;
    std::cout << a2.owner() << " 利息: " << a2.interest() << std::endl;
    std::cout << a3.owner() << " 利息: " << a3.interest() << std::endl;

    // 通过对象也能调用 static 成员函数（但不推荐，建议用类名）
    std::cout << "\n通过对象调用 static 函数 get_count(): "
              << a1.get_count() << std::endl;

    // 说明：static 成员函数没有 this，不能声明为 const。
    //   下面这行若取消注释会编译错误（static 与 const 不能同时用于成员函数，
    //   因为 const 是修饰 this 的，而 static 函数没有 this）。
    // static double bad() const;   // 错误

    return 0;
}
