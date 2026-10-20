#include <iostream>
#include "Sales_data13.1.h"

using std::cout;
using std::endl;

Sales_data fn(Sales_data d) {
	cout << "从一个返回类型为非引用类型的函数返回一个对象：";
	return d;
}

int main() {
	Sales_data data1("data1", 1, 1);

	cout << "使用一个对象初始化另一个对象" << endl;
	cout << "Sales_data data2(data1); ";
	Sales_data data2(data1);

	cout << "Sales_data data3 = data1; ";
	Sales_data data3 = data1;

	cout << "用花括号列表初始化一个数组中的元素或一个聚合类中的成员：";
	Sales_data datas[] = { data1 };

	cout << "将对象作为实参传递给一个非引用类型的形参：";
	fn(data1);
	
	return 0;
}
