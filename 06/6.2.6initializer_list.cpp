/*
	为了编写能处理不同数量实参的函数，C++11 标准提供了两种主要的方法
		如果所有的实参类型相同，可以传递一个名为 initializer_list 的标准库类型，定义在 initializer_list 头文件
		如果实参的类型不同，可以编写一种特殊的函数：可变参数模板

		C++还有一种特殊的形参类型（即省略符），可以用它传递可变数量的实参，这种功能一般只用于与 C函数交互的接口程序
*/

#include <iostream>
#include <initializer_list>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::initializer_list;

/*
	initializer_list 也是一种模板类型，定义 initializer_list 对象时，必须说明列表所含元素的类型
*/
void error_msg(int errorCode, initializer_list<string> il) {
	cout << "errorCode: " << errorCode << endl;
	for (auto beg = il.begin(); beg != il.end(); ++beg) {
		cout << *beg << " ";
	}
	cout << endl;
}


int main() {
	// 如果想向 initializer_list 形参中传递一个值的序列，则必须把序列放在一对花括号内
	string expected = "ok";
	string actual = "wrong";
	if (expected == actual) {
		error_msg(0, { "function", "okey" });
	}
	else {
		error_msg(1, { "functionX", expected, actual });
	}
	return 0;
}
