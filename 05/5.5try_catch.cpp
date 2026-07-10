// ===========================================================================
//  《C++ Primer》5.5 节示例：try / catch 异常处理
// ---------------------------------------------------------------------------
//  本程序：实现一个除法函数 divide(a, b)，当除数 b 为 0 时抛出
//          std::runtime_error 异常；在 main 中用 try/catch 捕获并处理。
//
//  要点：
//    1. throw 表达式抛出一个异常对象，类型通常为标准异常类。
//    2. try 块把可能抛异常的代码包起来；其后跟一个或多个 catch 子句。
//    3. catch 子句的「异常声明」通常用 const 引用：
//         catch (const std::runtime_error &e)
//       用引用避免拷贝、用 const 防止误改，并能多态捕获派生类对象。
//    4. 异常传播：throw 之后，函数立即中断，沿调用链向上查找匹配的 catch。
//       若一直未被捕获，最终到达 std::terminate，程序 abort。
//    5. 异常类层次见 <stdexcept>：
//         std::exception
//           ├── std::logic_error        （程序逻辑错误，如 invalid_argument）
//           └── std::runtime_error      （运行时错误，如除零、溢出）
//       what() 返回 const char* 描述信息。
// ===========================================================================
#include <iostream>
#include <stdexcept>               // std::runtime_error 在此头文件中
#include <string>

// 除法函数：除数为 0 时抛出 std::runtime_error
int divide(int a, int b)
{
    if (b == 0) {
        // throw 抛出一个异常对象，类型为 std::runtime_error
        // 构造时传入错误信息字符串，可通过 what() 取回
        throw std::runtime_error("除数不能为 0");
    }
    return a / b;
}

int main()
{
    int x = 0, y = 0;
    std::cout << "请输入被除数和除数（整数）：";
    std::cin >> x >> y;

    try {
        // try 块：包住可能抛异常的代码
        int result = divide(x, y);
        std::cout << "结果 = " << result << std::endl;
    } catch (const std::runtime_error &e) {
        // catch 子句：捕获 std::runtime_error（及其派生类）
        // 用 const 引用：避免对象切片、避免拷贝
        std::cerr << "发生异常：" << e.what() << std::endl;
        // e.what() 返回构造时传入的 "除数不能为 0"
        return 1;                  // 异常情况下返回非 0 表示出错
    }

    // 若 try 块正常结束（未抛异常），继续执行 catch 之后的语句
    std::cout << "除法运算正常完成。" << std::endl;
    return 0;
}
