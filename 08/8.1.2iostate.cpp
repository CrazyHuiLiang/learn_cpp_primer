#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

int main()
{
    int ival;
    cout << "请输入一个数字：" << endl;

    // 一个流一旦发生错误，其后续的 IO 操作都会失败，只有当一个流处于无错状态时，我们才可以从它读取数据，向它写入数据。确定一个流对象的状态最简单的方法是将它当做一个条件来使用。

    if (cin >> ival) {
        cout << "成功输入了一个数字：" << ival << endl;
    }
    else {
        cout << "失败，接收到的不是数字" << endl;
    }

    // IO 库定义了一个与机器无关的 iostate 类型，它提供了表达流状态的完整功能。这个类型应作为一个位集合来使用。
    // 流对象的 rdstate（） 成员返回一个 iostate 值，对应流的状态。
    auto old_state = cin.rdstate();

    // 注意：goodbit 的值为 0（eofbit=1, failbit=2, badbit=4），
    // `old_state & cin.goodbit` 恒为 0，永远检测不到；good 表示"没有任何错误位被置位"，只能整体比较是否为 0
    cout << "bit values:"
        << " goodbit " << cin.goodbit // 0
        << " eofbit " << cin.eofbit   // 1
        << " failbit " << cin.failbit // 2
        << " badbit " << cin.badbit   // 4
        << endl;
    cout << "cin iostate:"
        << ((old_state & cin.failbit) ? " failbit" : "") // 在发生可恢复错误后，failbit 被置位，如期望读取数值却读到一个字符等错误
        << ((old_state & cin.badbit) ? " badbit" : "")   // badbit 表示系统级错误，如不可恢复的读写错误，一旦 badbit 被置位，流就无法再使用了
        << ((old_state & cin.eofbit) ? " eofbit" : "")   // 如果到达文件结尾位置，eofbit 和 failbit 都会被置位
        << ((old_state == cin.goodbit) ? " goodbit" : "") // goodbit 的值为0，表示流未发生错误。
        << endl;
    // 也有一些流的谓词函数提供等价功能
    cout << "cin iostate:"
        << (cin.fail() ? " failbit | badbit" : "")
        << (cin.bad() ? " badbit" : "")
        << (cin.eof() ? " eofbit" : "")
        << (cin.good() ? " goodbit" : "")
        << endl;

    // setstate(flags) 将给定条件位置位，表示发生了对应的错误；setstate(s) 是"追加"（只把 s 里的位或进去，已有的位不动），等价于 clear(rdstate() | state)
    cin.setstate(cin.eofbit);
    cout << "eofbit 已置位 ";
    cout << "cin iostate:"
        << (cin.fail() ? " failbit | badbit" : "")
        << (cin.bad() ? " badbit" : "")
        << (cin.eof() ? " eofbit" : "")
        << (cin.good() ? " goodbit" : "")
        << endl;


    // clear 不接受参数的版本清除所有错误标志位
    cin.clear();
    cout << "已 clear ";
    cout << "cin iostate:"
        << (cin.fail() ? " failbit | badbit" : "")
        << (cin.bad() ? " badbit" : "")
        << (cin.eof() ? " eofbit" : "")
        << (cin.good() ? " goodbit" : "")
        << endl;

    // 带参数的 clear 版本接受一个 iostate 值，表示流的新状态；clear(s) 是"覆盖"（把整个状态赋值为 s）
    cin.clear(cin.badbit);
    cout << "clear(cin.badbit)";
    old_state = cin.rdstate();
    cout << "cin iostate:"
        << ((old_state & cin.failbit) ? " failbit" : "") 
        << ((old_state & cin.badbit) ? " badbit" : "")   
        << ((old_state & cin.eofbit) ? " eofbit" : "")   
        << ((old_state == cin.goodbit) ? " goodbit" : "")
        << endl;

    cout << std::unitbuf; // 所有输出操作后都会立即刷新缓冲区
    cout << "立即输出";
    cout << std::nounitbuf; // 回到正常的缓冲方式

    return 0;
}
