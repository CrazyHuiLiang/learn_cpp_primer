#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;


// 不能拷贝 unique_ptr 的规则有一个例外，我们可以拷贝或赋值一个将要销毁的 unique_ptr,最常见的例子是从函数返回一个 unique_ptr,编译器知道要返回的对象将要被销毁，会执行一种特殊的拷贝
unique_ptr<int> clone(int p) {
	unique_ptr<int> p1(new int(p));
	cout << "clone p:" << *p1 << endl;
	return p1;
}

void deletor(int *p) {
	cout << "deletor called:" << *p << endl;
	delete p;
}


int main() {
	// 没有类似 make_shared 的标准库函数返回 unique_ptr，当我们定义一个 unique_ptr 时，需要将其绑定一个 new 返回的指针
	unique_ptr<int> p2(new int(__LINE__));
	cout << "*p2:" << *p2 << endl;

	// 由于 unique_ptr 独占它所指向的对象，因此不支持普通的拷贝或赋值
	//unique_ptr<int> p1 = p2; // 报错

	// 但可以通过 release 或 reset 将指针的所有权从一个（非 const）unique_ptr 转移到另一个 unique
	unique_ptr<int> p1(p2.release());
	cout << "*p1:" << *p1 << endl;

	// reset 成员接受一个可选的指针参数，令 unique_ptr 重新指向给定的指针。如果 unique_ptr 不为空，它原来指向的对象被释放
	p1.reset(new int(__LINE__));
	cout << "*p1:" << *p1 << endl;


	unique_ptr<int> p3(clone(__LINE__));
	cout << "*p3:" << *p3 << endl;

	// 我们可以重载一个 unique_ptr 的删除器，必须在尖括号中指向类型之后提供删除器的类型
	//unique_ptr<int, decltype(deletor)> p4(new int(__LINE__), deletor);  // 删除器类型必须是一个可实例化的类型，因为 unique_ptr 内部会存储一个该类型的对象作为成员，deletor 是一个函数类型，函数类型不能作为对象存储（函数不是对象，没有大小，无法实例化成员变量），因此会编译报错

	unique_ptr<int, decltype(deletor)*> p4(new int(__LINE__), deletor); // 可以使用函数指针类型
	unique_ptr<int, decltype(&deletor)> p5(new int(__LINE__), deletor); // 使用 decltype 和引用的语法获取函数指针类型

	return 0;
}
