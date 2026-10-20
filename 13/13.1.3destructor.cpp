#include <iostream>
#include <memory>
#include <vector>
#include "Sales_data13.1.h"

using std::cout;
using std::endl;
using std::vector;

void fn() {
	// 栈上对象在离开作用域时析构
	Sales_data data1("data", 1, 1);

	{
		cout << "智能指针在引用计数为0后析构" << endl;
		auto p2 = std::make_shared<Sales_data>();
		p2->setNo("p2");
	}
	{
		cout << "\n容器中的对象在容器释放时析构" << endl;
		vector<Sales_data> vec;
		vec.push_back(data1);
		data1.setNo("data1");
	}
	{
		cout << "\n动态分配的对象，调用 delete 后析构" << endl;
		Sales_data* p = new Sales_data;
		p->setNo("p");
		delete p;
	}

	cout << "\n栈上对象在离开作用域时析构" << endl;
}

int main() {
	fn();
	cout << "end" << endl;
	return 0;
}
