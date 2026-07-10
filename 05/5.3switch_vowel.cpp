// ===========================================================================
//  《C++ Primer》5.3 节示例：switch 语句
// ---------------------------------------------------------------------------
//  本程序：统计输入文本中各元音字母 a/e/i/o/u 的出现次数。
//          大小写归并（A 与 a 都计入 a）。
//
//  要点：
//    1. switch 表达式必须是整型或枚举类型（char 也是整型）。
//    2. case 标签必须是「整型常量表达式」——不能是变量、不能是浮点。
//    3. 每个分支末尾要写 break；否则会发生「fall-through」（贯穿），
//       即不跳出 switch 而是继续执行下一个分支的语句。
//       ——忘记 break 是 switch 最常见的 bug。
//       （本程序特意在 'a'/'A' 分支演示一个有意的 fall-through 注释。）
//    4. default 分支处理所有未匹配 case 的情况，通常用于「兜底」。
//    5. 若需要在 switch 内部定义变量，应把变量及其使用放在一对花括号 { } 中，
//       形成块作用域，避免「跨过带初始化的变量定义」而引发编译错误。
// ===========================================================================
#include <iostream>
#include <string>

int main()
{
    std::cout << "请输入一段文本，按 Ctrl+Z(Windows) 或 Ctrl+D(Unix) 结束输入：" << std::endl;

    // 五个元音的计数器，全部初始化为 0
    unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0;
    char ch;                       // 逐字符读取
    while (std::cin >> ch) {       // 条件中读取：读到 EOF 时循环结束
        // 小写化：把大写元音归并到小写，简化 switch 结构
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));

        switch (ch) {              // switch 表达式为整型(char)
        case 'a':                  // case 标签：整型常量表达式 'a'
            ++aCnt;
            // 这里故意不写 break 演示 fall-through：若忘记 break，
            // 程序会继续执行下一个 case 的语句。本例中我们「不希望」贯穿，
            // 所以下一行补上 break（请始终记得写 break，除非确有贯穿意图）。
            break;
        case 'e':
            ++eCnt;
            break;
        case 'i':
            ++iCnt;
            break;
        case 'o':
            ++oCnt;
            break;
        case 'u':
            ++uCnt;
            break;
        default:                   // 兜底：非元音字符一律忽略
            // default 分支可省略 break（已是最后一条），但写上更清晰、
            // 也便于以后新增 case 时不易出错
            break;
        }
    }

    std::cout << "元音统计结果：" << std::endl;
    std::cout << "a: " << aCnt << std::endl;
    std::cout << "e: " << eCnt << std::endl;
    std::cout << "i: " << iCnt << std::endl;
    std::cout << "o: " << oCnt << std::endl;
    std::cout << "u: " << uCnt << std::endl;

    return 0;
}
