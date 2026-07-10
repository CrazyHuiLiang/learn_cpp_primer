// ===========================================================================
//  《C++ Primer》3.1 节示例：using 声明
// ---------------------------------------------------------------------------
//  为什么要用 using 声明：
//    - 标准库的名字都在命名空间 std 中，全名是 std::cin、std::cout 等。
//    - 每次都写 std:: 太繁琐；using 声明让我们「按名字」单独引入某个名字，
//      之后可直接用 cin、cout、endl，不必再加 std:: 前缀。
//
//  形式：
//      using std::cin;       // 以后用 cin 就等于 std::cin
//      using std::cout;
//      using std::endl;
//
//  重要建议：
//    1. using 声明一次只引入一个名字，作用清晰、可控；
//       切勿图省事写「using namespace std;」全局展开命名空间，
//       那样会污染当前作用域，容易引发名字冲突，尤其在头文件中危害更大。
//    2. 【头文件中不要使用 using 声明】！
//       头文件会被很多源文件包含，一旦里面写了 using，所有包含它的源文件
//       都会被强制引入相应名字，可能产生意料之外的冲突。using 声明应
//       限制在源文件（.cpp）的函数内或文件作用域内使用。
//
//  本程序：在 main 内用 using 声明引入 cin/cout/endl/string，演示简化写法。
// ===========================================================================
#include <iostream>
#include <string>

int main()
{
    // 在函数内部做 using 声明：作用域局限在 main 中，安全可控
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;     // string 也可以这样引入，之后直接写 string

    cout << "请输入你的名字：" << endl;
    string name;           // 等价于 std::string name;
    cin >> name;           // 等价于 std::cin >> name;

    cout << "你好，" << name << "！" << endl;
    return 0;
}
