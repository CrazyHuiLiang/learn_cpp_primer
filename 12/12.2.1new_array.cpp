#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;
using std::make_shared;

int main() {
	// 为了让 new 分配一个对象数组，我们要在类型名之后分一对方括号，其中指明要分配的对象的数目，方括号中的大小必须是整型，但不必是常量
	int size = __LINE__;
	int* pia = new int[size]; // 返回指向第一个元素的地址

	// 也可以使用表示数组类型的类型别名
	typedef int arrT[42];
	int* p = new arrT; // 分配一个 42 个 int 的数组，p指向第一个 int
	// 分配的内存并不是一个数组类型，而是得到一个数组元素类型的指针，因此不能对动态数组调用 begin 或 end，出于相同原因，也不能用范围 for 语句来处理动态数组中的元素

	// 可以对数组中的元素进行值初始化，方法是在大小之后跟一对空括号
	int* pia1 = new int[10]; // 10 个未初始化的 int
	int* pia2 = new int[10](); // 10 个初始化为 0 的 int
	std::string* psa = new std::string[10](); // 10 个空 string

	// 新标准中，可以提供一个元素初始化器的花括号列表
	// 如果初始化器数目小于元素数目，剩余元素将进行值初始化
	// 如果初始化器数目大于元素数目，则 new 表达式失败，不会分配任何内存
	int* pia3 = new int[10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	// 当我们用 new 分配一个大小为 0 的数组时，new 返回一个合法的非空指针，此指针保证与 new 返回的其他任何指针都不相同
	// 对于零长度的数组来说，此指针就像尾后指针一样，我们可以像使用尾后迭代器一样使用这个指针（可以加减运算进行移动、比较），但不能解引用，毕竟它不指向任何元素（会读出不确定的值）
	int* pia4 = new int[0];
	pia4++;
	cout << *pia4 << endl;

	// 为了释放动态数组，我们使用一种特殊形式的 delete，在指针前加上一个空方括号对
	// 数组中的元素是按逆序销毁
	delete[] pia;
	delete[] pia1;
	delete[] pia2;
	delete[] pia3;
	//delete[] pia4; // 长度为0的指针数组也不能 delete，会报错
	delete[] psa;


	// 可以使用 unique_ptr 管理 new 分配的数组，必须在对象类型后面跟一对空方括号
	unique_ptr<int[]> up(new int[size]()); // 类型说明符中的方括号(<int[]>) 指出 up 指向一个 int 数组

	// 当一个 unique_ptr 指向一个数组时，我们不能用点和箭头成员运算符，浙西运算符是无意义的，我们可以使用下标运算符来访问数组中的元素
	for (size_t i = 0; i != size; i++) {
		up[i] = i;
	}
	up.release(); // 自动用 delete[] 销毁其指针


	// shared_ptr 不直接管理动态数组，因为 shared_ptr 默认使用 delete 销毁它所指的对象
	// 如果希望使用 shared_ptr 管理一个动态数组，必须提供自己定义的删除器
	shared_ptr<int> sp(new int[size], [](int* p) {
		cout << "sp delete[]" << endl;
		delete[] p;
	});
	// shared_ptr 不直接支持动态数组管理这一特性会影响我们如何访问数组中的元素
	// shared_ptr 未定义下标运算符，并不支持指针的算术运算，必须用 get 获取一个内置指针，然后用它来访问数组元素
	for (size_t i = 0; i < size; i++) {
		*(sp.get() + i) = i; // 使用 get 获取一个内置指针
	}

	return 0;
}
