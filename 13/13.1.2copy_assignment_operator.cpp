#include <iostream>
#include "Sales_data13.1.h"

using std::cout;
using std::endl;

int main() {
	Sales_data data1("data1", 1, 1);
	Sales_data data2("data2", 2, 2);

	cout << "将一个对象赋值给另一个对象时，会触发被赋值对象的拷贝赋值运算符：";
	data2 = data1;
	
	return 0;
}
