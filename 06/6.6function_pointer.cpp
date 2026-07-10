// ===========================================================================
//  《C++ Primer》6.6 节示例：函数指针
// ---------------------------------------------------------------------------
//  要点：
//    - 函数指针指向某个具体函数，可通过它间接调用函数。
//    - 定义方式：返回类型 (*名)(形参列表)。可用 typedef / using 起别名。
//    - 函数名会隐式转换成函数指针（取地址 & 可省略）。
//    - 函数指针可作形参、作返回值。
//    - 函数指针数组可实现简单的「调度表」。
//
//  本程序：以四则运算为例演示上述各项。
// ===========================================================================
#include <iostream>

// 三个普通函数：二元整数运算
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

// 1) 用 using 起函数指针类型别名
using BinOp = int (*)(int, int);
// 等价的 typedef 写法：
// typedef int (*BinOp)(int, int);

// 2) 函数指针作形参：apply(op, a, b) 用传入的函数指针计算
int apply(BinOp op, int a, int b)
{
    return op(a, b);   // 通过函数指针调用函数
}

// 3) 函数指针作返回值：根据字符选择对应的运算函数
BinOp select_op(char c)
{
    switch (c) {
        case '+': return add;
        case '-': return sub;
        case '*': return mul;
        default:  return nullptr;
    }
}

int main()
{
    // 函数名即函数指针：& 可省略
    BinOp op1 = add;        // 等价于 &add
    std::cout << "add(3,4) = " << op1(3, 4) << std::endl;

    // 函数指针作形参
    std::cout << "apply(sub, 10, 4) = " << apply(sub, 10, 4) << std::endl;

    // 函数指针作返回值
    BinOp op2 = select_op('*');
    if (op2) {
        std::cout << "select_op('*')(5,6) = " << op2(5, 6) << std::endl;
    }

    // 4) 函数指针数组做简单调度
    BinOp ops[3] = {add, sub, mul};
    const char *names[3] = {"add", "sub", "mul"};
    int a = 20, b = 5;
    for (int i = 0; i < 3; ++i) {
        std::cout << names[i] << "(" << a << "," << b << ") = "
                  << ops[i](a, b) << std::endl;
    }
    return 0;
}
