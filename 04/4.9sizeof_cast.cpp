// ===========================================================================
//  《C++ Primer》4.9 节示例：sizeof 运算符与显式类型转换
// ---------------------------------------------------------------------------
//  要点：
//  A. sizeof 运算符
//    1. 返回「对象或类型所占字节数」，结果类型为 std::size_t，编译期求值。
//    2. 四种形式：
//         sizeof(type)          例：sizeof(int)
//         sizeof expr           例：sizeof x      （对表达式，不求值 expr）
//         sizeof(expr)          例：sizeof(x)
//         sizeof <expr>  （旧式，不推荐）
//    3. sizeof 不实际求值其表达式（除非对 VLA，C++ 一般没有）：
//       sizeof *p 不需要 p 有效；sizeof a[i] 不会真的访问 a[i]。
//    4. 求数组元素个数：sizeof(arr) / sizeof(arr[0])
//       —— 数组作为 sizeof 的操作数不会退化为指针。
//    5. 对 string/vector 等，sizeof 返回「该类型对象本身的大小」
//       （固定开销，不含动态分配的元素），而非元素个数。
//
//  B. 显式类型转换（命名的 cast）
//    1. static_cast<type>(expr)  —— 最常用，做「明确定义」的转换：
//         · 数值类型之间（int↔double、int↔char 等）
//         · void* ↔ 具体指针类型
//         · 不去掉 const
//    2. const_cast<type>(expr)   —— 只用于增删 const/volatile：
//         · 典型场景：调用的旧式 C API 形参是 T*，但手上只有 const T*
//         · 若底层对象本身是 const，通过 const_cast 写它是 UB
//    3. dynamic_cast<type>(expr) —— 运行时安全向下转型（用于继承体系，需多态）
//         本示例不展开（见第 19 章虚函数/RTTI）。
//    4. reinterpret_cast<type>(expr) —— 按位重新解释指针/整型，
//         极度危险、平台相关，本示例「不写实际代码」，仅作说明。
//    5. 避免旧式 C 转换 (type)expr —— 它等价于依次尝试上述几种 cast，
//       出错时编译器无从警告，应使用命名的 cast 让意图显式。
// ===========================================================================
#include <iostream>
#include <vector>
#include <string>

int main()
{
    // =================== sizeof ===================
    std::cout << "=== sizeof 运算符 ===\n";

    // 1. 对「类型」求大小
    std::cout << "sizeof(char)    = " << sizeof(char)     << " 字节\n"; // 1
    std::cout << "sizeof(short)   = " << sizeof(short)    << " 字节\n";
    std::cout << "sizeof(int)     = " << sizeof(int)      << " 字节\n";
    std::cout << "sizeof(long)    = " << sizeof(long)     << " 字节\n";
    std::cout << "sizeof(double)  = " << sizeof(double)   << " 字节\n";
    std::cout << "sizeof(size_t)  = " << sizeof(std::size_t) << " 字节\n";

    // 2. 对「变量/表达式」求大小
    int x = 42;
    double d = 3.14;
    std::cout << "sizeof x   = " << sizeof x   << '\n';   // 同 sizeof(int)
    std::cout << "sizeof d   = " << sizeof d   << '\n';   // 同 sizeof(double)
    std::cout << "sizeof(x + d) = " << sizeof(x + d) << '\n'; // 算术提升为 double

    // 3. sizeof 不实际求值表达式：即使指针未初始化，也安全
    int* p = nullptr;
    std::cout << "sizeof *p  = " << sizeof(*p) << "  (*p 不会被求值，安全)\n";

    // 4. 用 sizeof 求数组元素个数（数组不退化为指针）
    int arr[] = {10, 20, 30, 40, 50};
    constexpr std::size_t arr_cnt = sizeof(arr) / sizeof(arr[0]);
    std::cout << "sizeof(arr)     = " << sizeof(arr)      << '\n';
    std::cout << "sizeof(arr[0])  = " << sizeof(arr[0])   << '\n';
    std::cout << "元素个数 = " << arr_cnt << '\n';        // 5

    // 5. string / vector：sizeof 返回类型固定大小，不是元素数！
    std::vector<int> vec(1000, 7);
    std::string s = "hello world";
    std::cout << "sizeof(std::string) = " << sizeof(std::string) << "  (固定开销，不含字符数据)\n";
    std::cout << "sizeof(s)           = " << sizeof(s)           << "  (与内容长度无关)\n";
    std::cout << "sizeof(std::vector<int>) = " << sizeof(std::vector<int>)
              << "  (固定开销，不含 1000 个元素)\n";
    std::cout << "sizeof(vec)         = " << sizeof(vec)
              << "  (与元素个数无关；元素数请用 vec.size())\n";

    // =================== 显式类型转换 ===================
    std::cout << "\n=== 显式类型转换 ===\n";

    // --- static_cast：数值转换 ---
    char c = 'A';
    int code = static_cast<int>(c);              // char -> int
    std::cout << "char '" << c << "' 的 ASCII = " << code << '\n';

    double pi = 3.14159;
    int truncated = static_cast<int>(pi);        // double -> int，截断小数
    std::cout << "static_cast<int>(3.14159) = " << truncated << '\n'; // 3

    int n = 10, m = 4;
    // 整数除法会截断；用 static_cast 把一个操作数提升为 double 做浮点除法
    double ratio = static_cast<double>(n) / m;
    std::cout << "static_cast<double>(10) / 4 = " << ratio << '\n';   // 2.5

    // --- static_cast：void* 与具体指针互转 ---
    int value = 1234;
    void* vp = &value;                           // 任何对象指针都可隐式转 void*
    std::cout << "void* vp 指向某个 int\n";
    // 通过 void* 取回原类型必须用 static_cast（且类型必须匹配原对象类型）
    int* ip = static_cast<int*>(vp);
    std::cout << "通过 static_cast<int*>(vp) 取回: " << *ip << '\n';  // 1234

    // --- const_cast：增删 const ---
    const int ci = 100;
    // int* bad = &ci;            // 编译错误：const int* 不能隐式转 int*
    int* modifiable = const_cast<int*>(&ci);     // 去掉 const，仅改指针类型
    std::cout << "const_cast 后 *modifiable = " << *modifiable << '\n';

    // ！！！危险！！！：若底层对象本身是 const，通过 const_cast 写它是 UB。
    //   *modifiable = 200;   // UB：ci 是真正的 const 对象
    // 合法用法示例：旧式 API 形参为 char*，但手上只有 const char*
    const char* cstr = "literal";
    // 假设有 API: void legacy_api(char* s);
    // legacy_api(const_cast<char*>(cstr));  // 仅当 legacy_api 不修改 s 时安全
    // 这里仅演示转换本身，并打印长度以避免变量未使用：
    char* cstr_nc = const_cast<char*>(cstr);
    std::cout << "const_cast<char*>(\"" << cstr_nc << "\") 演示完成（未实际写底层 const 对象）\n";

    // --- reinterpret_cast：仅注释说明，不写危险代码 ---
    // reinterpret_cast 用于在「不相关」的指针类型之间、指针与整型之间按位重新解释。
    //   int* p1 = ...;
    //   char* pc = reinterpret_cast<char*>(p1);  // 把 int 内存按字节看
    //   uintptr_t n = reinterpret_cast<uintptr_t>(p1); // 指针转整数
    // 它高度平台相关、极易引发别名/对齐/生命周期问题，
    // 除极少数底层场景（如序列化、与硬件寄存器交互）外应避免使用。

    // --- 避免旧式 C 转换 ---
    // 旧式写法 (type)expr 同时覆盖 static_cast/const_cast/reinterpret_cast 的语义，
    // 编译器无法根据「你的意图」给出精确警告，建议一律改用命名的 cast：
    //   double dd = (double)n / m;       // 旧式，不推荐
    //   double dd = static_cast<double>(n) / m;  // 推荐：意图清晰

    return 0;
}
