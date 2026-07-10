// ===========================================================================
//  《C++ Primer》6.2 节示例：main 的命令行参数
// ---------------------------------------------------------------------------
//  要点：
//    - int main(int argc, char *argv[]) 也可写作 char **argv。
//    - argv[0] 是程序名（可能是空串，取决于实现）。
//    - argv[1] ... argv[argc-1] 是命令行参数（按出现顺序）。
//    - argv[argc] 保证为 nullptr，可作为遍历终止条件。
//    - argc 至少为 1（即 argv[0] 一定存在）。
//
//  演示：打印 argc 与每个 argv[i]。可在命令行带参数运行，例如：
//      6_2main_args foo bar "third arg"
// ===========================================================================
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "argc = " << argc << std::endl;
    std::cout << "argv[argc] == nullptr ? "
              << std::boolalpha << (argv[argc] == nullptr) << std::endl;

    // 逐个打印：i 从 0 到 argc（含）���argv[argc] 一定是 nullptr
    for (int i = 0; i <= argc; ++i) {
        std::cout << "argv[" << i << "] = ";
        if (argv[i] == nullptr) {
            std::cout << "(nullptr)";
        } else {
            std::cout << "\"" << argv[i] << "\"";
        }
        std::cout << std::endl;
    }
    return 0;
}
