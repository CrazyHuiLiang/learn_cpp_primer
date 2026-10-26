#include <iostream>
#include <vector>
#include <new>
#include <memory>

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;


// C++ 语言定义了两个运算符来分配和释放动态内存，new 分配内存，delete 释放 new 分配的内存
void new_and_delete() {

	// 在自由空间分配的内存是无名的，因此 new 无法为其分配的对象命名，而是返回一个指向该对象的指针
	int* pi = new int;
	// 默认情况下，动态分配的对象时默认初始化的
	//	   这意味着内置类型或组合类型的对象的值将是未定义的
	//     而类类型对象将用默认构造函数进行初始化
	cout << "默认初始化：" << *pi << endl;

	// 可以使用直接初始化的方式
	int* pi2 = new int(1024);
	cout << "直接初始化：" << *pi2 << endl;

	// 新标准下，也可以使用列表初始化
	vector<int>* pv = new vector<int>{ 0, 1, 2, 3, 4 };
	cout << "列表初始化：" << (*pv)[0] << endl;

	// 对动态分配的对象进行初始化通常是个好做法

		// 当括号中仅有一个初始化器时，可以使用 auto，从初始化器来推断我们要分配的对象类型
	auto p1 = new auto(1);
	cout << "使用 auto：" << *p1 << endl;

	// 一个动态分配的 const 对象必须进行初始化
	const int* pci = new const int(1024);
	//*pci = 5;
	cout << "动态分配对象：" << *pci << endl;


	// 一旦一个程序用光了它可用的所有可用的内存，new 表达式就会抛出一个类型为 bad_alloc 的异常
	// 我们可以改变使用 new 的方式来阻止它抛出异常，这种形式的 new 为定位new（placment new），定位new表达式允许我们向 new 传递额外的参数
	// 如果将 nothrow 传递给 new，我们的意图是告诉它不能抛出异常，这种形式的 new 不能分配所需内存时会返回一个空指针
	int* p3 = new (std::nothrow)int; // 如果分配失败会返回一个空指针，bad_alloc 和 nothrow 都定义在头文件 new 中

	// 释放动态内存
		// delete 表达式接受一个动态分配的对象或者指针
	delete pi;
	delete pi2;
	delete pv;
	delete p1;
	delete pci;
	delete p3;

	// 释放一块非 new 分配的内存，或者将相同的指针值释放多次，其行为是未定义的
	// 在 delete 之后，指针就变成了人们所说的空悬指针，即，指向一块曾经保存数据对象但现在已经无效的内存的指针
	// 可以在 delete 之后将 nullptr 赋予指针，这样就清楚地指出指针不指向任何对象
	pi = nullptr;
	pi2 = nullptr;
	pv = nullptr;
	p1 = nullptr;
	pci = nullptr;
	p3 = nullptr;

	// 动态内存的一个基本问题是可能有多个指针指向相同的内存，在 delete 内存之后重置指针只对这个指针有效，对其他任何仍指向（已释放的）内存的指针是没有作用的
	int* p(new int(42));
	auto q = p;
	delete p;	// 这时 p 和 q 都已无效
	cout << p << ":" << q << endl;
	p = nullptr;
	cout << p << ":" << q << endl;
}


// 练习12.6
vector<int>* e12_6_new(int size) {
	return new vector<int>(size);
}
vector<int>* e12_6_in(vector<int>* v, int size) {
	for (int i = 0; i<size; i++)
		std::cin >> (*v)[i];
	return v;
}
vector<int>* e12_6_out(vector<int>* v, int size) {
	for (int i = 0; i < size; i++)
		std::cout << (*v)[i] << " ";
	cout << endl;
	return v;
}

// 练习12.7
shared_ptr<vector<int>> e12_7_new(int size) {
	return std::make_shared<vector<int>>(size);
}
shared_ptr<vector<int>> e12_7_in(shared_ptr<vector<int>> v, int size) {
	for (int i = 0; i < size; i++)
		std::cin >> (*v)[i];
	return v;
}
shared_ptr<vector<int>> e12_7_out(shared_ptr<vector<int>> v, int size) {
	for (int i = 0; i < size; i++)
		std::cout << (*v)[i] << " ";
	cout << endl;
	return v;
}



int main() {
	new_and_delete();

	int size = 2;
	cout << "请输入 " << size << " 个数字" << endl;
	delete e12_6_out(e12_6_in(e12_6_new(size), size), size);

	cout << "请输入 " << size << " 个数字" << endl;
	// shared_ptr 不需要考虑 delete
	e12_7_out(e12_7_in(e12_7_new(size), size), size);
	return 0;
}