// ===========================================================================
//  《C++ Primer》3.3 节示例：vector 基础
// ---------------------------------------------------------------------------
//  std::vector 是「动态数组」：能存放同类型对象的集合，运行时可增减元素。
//  它是 C++ 中最常用的容器之一。使用前需 #include <vector>。
//
//  vector 是「类模板(class template)」，需在 < > 中给出元素类型：
//      std::vector<int>        vi;     // 存 int 的空 vector
//      std::vector<std::string> vs;    // 存 string 的空 vector
//
//  本程序演示：
//    1. 多种初始化方式：默认、列表初始化、n 个相同值、拷贝初始化
//    2. push_back() 追加元素（运行时动态添加）
//    3. 范围 for 打印元素
//    4. size() 获取元素个数
//
//  【重要】下标只能访问「已存在」的元素，不能用来添加元素！
//    - 错误：std::vector<int> v;  v[0] = 1;   // v 是空的，v[0] 越界未定义！
//    - 正确：std::vector<int> v;  v.push_back(1);
//    - 下标运算符不检查越界；越界访问是未定义行为，可能程序崩溃或数据错乱。
// ===========================================================================
#include <iostream>
#include <vector>
#include <string>

int main()
{
    // ---- 1. 多种初始化方式 ----
    std::vector<int> v1;                       // 默认初始化：空 vector
    std::vector<int> v2 = {1, 2, 3, 4, 5};     // 列表初始化：5 个元素
    std::vector<int> v3(4, 100);               // 4 个值为 100 的元素
    std::vector<int> v4(v2);                   // 拷贝初始化：v4 是 v2 的副本
    std::vector<int> v5 = v3;                  // 等价于上一行的拷贝初始化
    std::vector<std::string> v6 = {"a", "bb", "ccc"};  // 列表初始化 string

    std::cout << "v2 列表初始化：";
    for (auto x : v2) std::cout << x << ' ';   // 范围 for 打印
    std::cout << "\n";

    std::cout << "v3 (4 个 100)：";
    for (auto x : v3) std::cout << x << ' ';
    std::cout << "\n";

    std::cout << "v4 (v2 的副本)：";
    for (auto x : v4) std::cout << x << ' ';
    std::cout << "\n";

    std::cout << "v6 (string 列表)：";
    for (const auto &s : v6) std::cout << "[" << s << "] ";  // 用 const& 避免拷贝
    std::cout << "\n";

    // ---- 2. push_back：运行时动态追加元素 ----
    // 这是从空 vector 开始构建内容的标准做法
    std::cout << "\n用 push_back 追加 0..4：";
    for (int i = 0; i < 5; ++i) {
        v1.push_back(i);                       // 把 i 追加到末尾
    }
    for (auto x : v1) std::cout << x << ' ';
    std::cout << "  (size = " << v1.size() << ")\n";

    // ---- 3. 下标访问「已存在」的元素 ----
    // 下标只能用于读写已存在的元素，绝不能用于添加元素
    std::cout << "v2[2] = " << v2[2] << "\n";  // 读：3
    v2[2] = 30;                                 // 写：修改第 3 个元素
    std::cout << "修改后 v2[2] = " << v2[2] << "\n";

    // 反面教材（注释说明，不执行）：
    //   std::vector<int> bad;   // 空 vector
    //   bad[0] = 1;             // 未定义行为！bad 里根本没有元素，不能下标赋值
    //   正确做法是 bad.push_back(1);

    // ---- 4. size() 返回 vector::size_type（无符号）----
    std::vector<int>::size_type n = v2.size();  // 用正确的类型接收
    std::cout << "v2.size() = " << n << "\n";

    return 0;
}
