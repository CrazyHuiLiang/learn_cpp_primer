// ===========================================================================
//  《C++ Primer》3.5 节示例：C 风格字符串
// ---------------------------------------------------------------------------
//  C 风格字符串是以「空字符 '\0'」结尾的字符数组，定义在 <cstring> 中：
//    - strlen(s)      返回 s 的长度（不计结尾 '\0'）
//    - strcpy(d, s)   把 s（含 '\0'）复制到 d；d 必须足够大
//    - strcat(d, s)   把 s 追加到 d 末尾；d 必须足够大
//    - strcmp(s1, s2) 按字典序比较；返回 0 表示相等，<0 表示 s1<s2，>0 表示 s1>s2
//
//  与 std::string 互转：
//    - string 能隐式转换为 C 字符串字面值初始化；
//    - string.c_str() 返回 const char* 指向内部以 '\0' 结尾的字符数组
//      （返回的指针在 string 改变后可能失效，使用前不要修改原 string）。
//
//  【强烈建议】现代 C++ 优先使用 std::string 和 std::vector：
//    - C 风格字符串/数组没有边界检查，容易越界、缓冲区溢出、忘记结尾 '\0'；
//    - 手工管理大小繁��易错，是大量安全漏洞的根源；
//    - string/vector 自动管理内存，提供丰富的成员函数，更安全也更高效。
//    本程序仅为说明 C 风格字符串的用法与注意事项，实际编码请用 string。
// ===========================================================================
#include <iostream>
#include <cstring>       // strlen, strcpy, strcat, strcmp
#include <string>        // std::string、c_str()

int main()
{
    // ---- 1. strlen：长度（不计 '\0'）----
    const char *cs = "hello";            // 字符串字面值，末尾自动有 '\0'
    std::cout << "strlen(\"" << cs << "\") = " << std::strlen(cs) << "\n";  // 5

    // ---- 2. strcpy：复制（目标必须足够大）----
    char buf[20];                        // 目标缓冲区，要足够容纳源串
    std::strcpy(buf, cs);                // 把 cs（含 '\0'）复制到 buf
    std::cout << "strcpy 后 buf = " << buf << "\n";

    // ---- 3. strcat：追加（目标缓冲区要够大）----
    std::strcat(buf, ", world!");        // 把 ", world!" 追加到 buf 末尾
    std::cout << "strcat 后 buf = " << buf << "\n";   // hello, world!

    // ---- 4. strcmp：比较 ----
    const char *s1 = "apple";
    const char *s2 = "banana";
    int r = std::strcmp(s1, s2);
    std::cout << "strcmp(\"" << s1 << "\", \"" << s2 << "\") = " << r
              << (r < 0 ? " (<0 表示前者小)\n" :
                  r > 0 ? " (>0 表示前者大)\n" :
                          " (0 表示相等)\n");

    // ---- 5. std::string 与 C 字符串互转 ----
    std::string str("C++ string");

    // string -> const char*：用 c_str()
    // 注意：返回 const char*，不能通过它修改 string 内容；
    //       若 string 后续被修改，之前拿到的 c_str() 指针可能失效。
    const char *cstr = str.c_str();
    std::cout << "str.c_str() = " << cstr << "\n";

    // const char* -> string：直接构造或赋值
    std::string from_cstr = buf;          // 用 C 字符串构造 string
    std::cout << "用 C 字符串构造 string = " << from_cstr << "\n";

    // ---- 6. 安全提示 ----
    // 下面这些写法都是危险的（注释说明，不要执行）：
    //   char small[3];
    //   std::strcpy(small, "hello");   // 溢出！目标只有 3 字节，源串要 6 字节
    //   const char *p = nullptr;
    //   std::strlen(p);                // 解引用空指针，未定义行为
    //
    // 用 std::string 可以彻底避免这类问题：
    std::string a = "hello";
    std::string b = a + ", " + "world";   // 自动管理内存，无需关心大小
    std::cout << "string 拼接 = " << b << "\n";
    if (a == "hello") {                   // string 直接用 == 比较，直观安全
        std::cout << "string 比较也简洁安全\n";
    }

    return 0;
}
