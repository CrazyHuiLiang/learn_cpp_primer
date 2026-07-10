// ===========================================================================
//  《C++ Primer》3.2 节示例：string 的常用操作
// ---------------------------------------------------------------------------
//  演示：
//    - empty()      判断是否为空串
//    - size()       返回字符数，类型为 string::size_type（无符号整数）
//    - 比较运算符   按字典序比较 <, <=, >, >=, ==, !=
//    - 相加          + 与 += 拼接 string、字符串字面值、字符
//    - 下标 s[i]    访问或修改第 i 个字符
//
//  关键概念：string::size_type
//    - size() 返回的不是 int，而是 string 内部定义的 size_type，
//      它是一个【无符号】整数类型（通常等价于 std::size_t）。
//    - 因此千万不要把 size() 的返回值与有符号 int 混在一起做比较或运算，
//      否则可能触发「有符号→无符号」的隐式转换，导致难以察觉的 bug：
//          int n = -1;
//          if (s.size() < n)   // n 被转成一个极大的无符号数，条件恒为假！
//    - 正确做法：用 auto 或 size_type 接收 size() 的返回值；
//      需要下标循环时优先用范围 for 或 size_type 类型的索引。
//
//  本程序：用一个 string 演示上述操作。
// ===========================================================================
#include <iostream>
#include <string>

int main()
{
    std::string s = "hello";
    std::string t = "world";

    // ---- empty() ----
    std::cout << "s = \"" << s << "\"\n";
    std::cout << "s.empty()? " << std::boolalpha << s.empty() << "\n";   // false
    std::string empty_s;
    std::cout << "empty_s.empty()? " << empty_s.empty() << "\n";         // true

    // ---- size() 与 size_type ----
    // 用 auto 让编译器推断为 string::size_type（无符号），避免 int 混用
    auto len = s.size();                  // 类型是 std::string::size_type
    std::cout << "s.size() = " << len << "\n";

    // 直接说明潜在陷阱（注释里演示，不实际编译执行错误逻辑）：
    //   int n = -1;
    //   if (s.size() < n) { ... }   // n 转为无符号后变成超大数，比较结果不符合预期

    // ---- 字典序比较 ----
    // 比较规则：逐字符按 ASCII 比较；短串是长串的前缀时，短串较小
    if (s < t) {
        std::cout << "\"" << s << "\" < \"" << t << "\" (字典序)\n";     // hello < world
    }
    std::cout << "(s == t)? " << (s == t) << "\n";                       // false

    // ---- 相加：+ 与 += ----
    std::string greeting = s + ", " + t + "!";   // string 之间、与字面值拼接
    std::cout << "拼接后：" << greeting << "\n";
    greeting += "!!";                            // 追加到自身
    std::cout << "追加后：" << greeting << "\n";

    // ---- 下标访问与修改 ----
    // s[i] 返回第 i 个字符的引用，既可读也可写
    std::cout << "s[0] = " << s[0] << "\n";      // h
    s[0] = 'H';                                  // 修改首字母为大写
    std::cout << "修改后 s = \"" << s << "\"\n"; // Hello

    // 用 size_type 作下标遍历（避免 int 与无符号混用）
    for (std::string::size_type i = 0; i != s.size(); ++i) {
        std::cout << "  s[" << i << "] = " << s[i] << "\n";
    }

    return 0;
}
