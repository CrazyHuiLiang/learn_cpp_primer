#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <deque>
#include <list>
#include <forward_list>

using std::cout;
using std::cin;
using std::endl;
using std::array;
using std::vector;
using std::string;
using std::deque;
using std::list;
using std::forward_list;

using vector_int = vector<int>;

void print_list(vector<int> &v) {
	auto v1_begin = v.begin();
	auto v1_end = v.end();
	// 使用迭代范围作为判断依据
	while (v1_begin != v1_end) {
		cout << *v1_begin << " ";
		v1_begin++;
	}
	cout << endl;
}


int main() {

	vector<int> v1;
	v1.push_back(1);
	print_list(v1);

	//- 初始化为拷贝
	vector<int> v2(v1);
	print_list(v2);

	vector<int> v3 = v1;
	print_list(v3);

	//	- 初始化为初始化列表中元素的拷贝
	//	- C c{ a, b, c, ... }
	vector_int c4{1, 2, 3};
	print_list(c4);
	//	- C c = { a, b, c... }
	vector_int c5 = { 1, 2, 3, 4 };
	print_list(c5);

	//	- 初始化为迭代器 b 和 e 指定范围中的元素的拷贝
	//	- C c(b, e);
	vector_int c6(c5.begin(), c5.end());
	print_list(c6);

	//-只有顺序容器（不包括 array）的构造函数接收大小参数
	//	- C c(n);    初始化为包含 n 个元素
	vector_int c7(7);
	print_list(c7); // 7个0

	//	- C c(n, t); 初始化为包含 n 个值为 t 的元素
	vector_int c8(8, 8);
	print_list(c8); // 8 个8


	// 当定义一个 array 时，除了指定元素类型，还要指定容器大小，大小是 array 类型的一部分，array 不支持普通的容器构造函数
	array<int, 9> c9;
	// 如果我们对 array 进行列表初始化，出事值得数目必须等于或晓雨 array 的大小
	array<int, 10> c10= {1};
	// 虽然不能对内置数组类型进行拷贝或对象赋值操作，但 array 并无此限制
	array<int, 10> c11 = c10;


	list<string> names;
	vector<const char*> oldstyle;
	//names = oldstyle;// 错误，容器类型不匹配
	// 顺序容器定义了一个名为 assign 的成员，允许我们从一个不同但相融的类型赋值，或者从容器的一个子序列赋值
	// assign 操作用参数所指定的元素的拷贝替换左边容器中的所有元素
	names.assign(oldstyle.cbegin(), oldstyle.cend());

	// assign 的第二个版本接受一个整型值和一个元素值，它用指定数目且具有相同给定值的元素替换容器中原有的元素
	names.assign(10, "bill"); // 10 个元素，都是 bill
	for (auto& item : names) {
		cout << item << " ";
	}
	cout << endl;

	list<string> names2;
	names2.assign(10, "annie");

	// swap 操作交换两个相同类型容器的内容，除 array 外，交换两个容器内容的操作保证会很快，元素本身并未交换，只是交换了两个容器的内部数据结构
	names.swap(names2);
	for (auto& item : names) {
		cout << item << " ";
	}
	cout << endl;

	// 新标准提供了非成员版本的 swap，统一使用非成员版嗯的 swap 是一个好习惯	
	std::swap(names, names2);
	for (auto& item : names) {
		cout << item << " ";
	}
	cout << endl;

	// 除了 forward_list ，每个容器类型都有三个与大小相关的操作
	cout << "成员函数 size 返回容器中元素的数目 " << names.size() << endl;
	cout << "empty 当 size 为0 时返回布尔值 true；" << (names.empty() ? "空" : "非空") << endl;
	// forward_list 不支持 size，但支持 max_size 和 empty
	cout << "max_size 成员 " <<  names.max_size() << endl;


	// 关系运算符左右两边的运算对象必须是相同类型的容器，且必须保存相同类型的元素，比较两个容器实际上是进行元素的逐对比较，这些运算符的工作方式与 string 的关系运算符类似
	cout << (names < names2 ? "names win" : "names2 win") << endl;

	// 只有当其元素类型也定义了相应的比较运算符时，我们才可以使用关系运算符来比较两个容器
	// 容器相等运算符实际上是使用 == 运算符实现比较的，其他关系运算符是使用元素的 < 运算符

	return 0;
}
