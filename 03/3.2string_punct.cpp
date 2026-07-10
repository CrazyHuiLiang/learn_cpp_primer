// ===========================================================================
//  《C++ Primer》3.2 节经典示例：处理 string 中的字符
// ---------------------------------------------------------------------------
//  演示：
//    1. 范围 for(range for) 遍历 string 的每个字符
//    2. 用 <cctype> 中的 ispunct 统计标点符号个数
//    3. 用 toupper 把整个 string 改成大写
//         - 要「修改」原串中的字符，范围 for 必须用「引用」变量：auto &c
//           （若写 auto c，则 c 是副本，修改不影响原串）
//
//  <cctype> 常用函数（参数与返回值都是 int，且传给它们的字符应转为 unsigned char）：
//    isalpha(c)  字母
//    isdigit(c)  数字
//    ispunct(c)  标点（非字母数字非空白的可打印字符）
//    isspace(c)  空白
//    isupper/islower(c) 大写/小写
//    toupper/tolower(c) 转大写/小写（非字母原样返回）
//
//  本程序：读入一行文本，统计其中的标点个数，并把整行转为大写后输出。
// ===========================================================================
#include <iostream>
#include <string>
#include <cctype>        // ispunct, toupper 等

int main()
{
    std::string line;
    std::cout << "请输入一行文字：" << std::endl;
    if (!std::getline(std::cin, line)) {
        return 0;        // 读取失败直接结束
    }

    // ---------------------------------------------------------------------
    // 一、统计标点符号个数：用范围 for（只读，不必用引用）
    // ---------------------------------------------------------------------
    // 范围 for：for (声明 : 序列) { ... }
    //   每次循环把序列中的一个元素赋给声明变量；这里我们只读，用 auto c 即可。
    std::string::size_type punct_cnt = 0;
    for (auto c : line) {                 // c 是 char 的副本（只读不改）
        if (ispunct(static_cast<unsigned char>(c))) {   // 是标点则计数
            ++punct_cnt;
        }
    }
    std::cout << "标点符号个数：" << punct_cnt << std::endl;

    // ---------------------------------------------------------------------
    // 二、把整行转为大写：要修改原串，范围 for 必须用「引用」auto &c
    // ---------------------------------------------------------------------
    // 关键：auto &c 让 c 成为对当前字符的引用，修改 c 即修改原串中的字符。
    //       若写成 for (auto c : line)，c 只是副本，toupper 不会影响 line。
    for (auto &c : line) {                // c 是对 line 中字符的引用
        c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
    }
    std::cout << "转为大写后：" << line << std::endl;

    return 0;
}
