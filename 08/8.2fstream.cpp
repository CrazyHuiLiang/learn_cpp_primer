#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#if defined(_WIN32)
#include <windows.h>
#endif

int main(int argc, char **argv)
{
    // 与本目标在 08/CMakeLists.txt 中的 /execution-charset:utf-8 成对使用：
    // 字面量以 UTF-8 写入 exe，控制台也必须按 UTF-8 解码，两者缺一即乱码。
    // 必须放在任何输出之前——否则下面的错误提示会以 UTF-8 字节发给还是 GBK 的控制台。
    #if defined(_WIN32)
        SetConsoleOutputCP(CP_UTF8);
    #endif

    if (argc != 2) {
        std::cout << "请输入文件路径!" << std::endl;
        exit(1);
    }

    std::string infile(*(argv + 1));
    std::ifstream ifstrm(infile);
    std::vector<std::string> vs1;
    while (ifstrm) {
        std::string tmp;
        ifstrm >> tmp;
        if (!tmp.empty()) {
            vs1.push_back(tmp);
        }
    }


    std::ofstream ofstrm(infile + ".copy");
    for (auto &tmp : vs1) {
        std::cout << tmp << std::endl;
        ofstrm << tmp << std::endl;
    }


    ifstrm.clear(); // 消除 EOF 及其他错误标志
    ifstrm.seekg(0);
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << "使用 getline 读取" << std::endl;
    std::string line;
    while (std::getline(ifstrm, line)) {
        std::cout << line << std::endl;
    }
    return 0;
}
