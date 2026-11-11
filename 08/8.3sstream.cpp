#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::istringstream;
using std::ostringstream;

struct PersonInfo {
    string name;
    vector<string> phones;
};

int main(int argc, char **argv)
{
    std::cout << "请输入 姓名 手机号 [手机号...]" << std::endl;
    string line, word;
    vector<PersonInfo> people;
    while (std::getline(std::cin, line)) {
        PersonInfo info;

        // 将流绑定到刚输入的行
        istringstream record(line);
        // 可以使用输入运算符读取流中的数据
        record >> info.name;
        // 循环从一个 string 读取数据，当 string 中的数据全部读出后，会触发文件结束信号
        while (record >> word) {
            info.phones.push_back(word);
        }
        people.push_back(info);
    }

    // 手机号为 11 位
    auto valid = [](const string& nums) -> bool {
        return nums.size() == 11;
    };


    // 当我们逐步构造输出，希望最后一起打印时，ostringstream 是很有用的
    for (const auto& entry : people) {
        ostringstream formatted, badNums;

        for (const auto& nums : entry.phones) {
            if (!valid(nums)) {
                badNums << " " << nums;
            }
            else {
                formatted << " " << nums;
            }
        }
        // 如果当前人的手机号输入没有错误
        if (badNums.str().empty()) {
            // 输出正确的手机号
            std::cout << entry.name << " " << formatted.str() << std::endl;
        }
        else {
            // 输出错误的手机号
            std::cout << entry.name << " input error " << badNums.str() << std::endl;
        }
    }
    return 0;
}
