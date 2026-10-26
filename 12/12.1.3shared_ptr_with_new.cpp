#include <iostream>
#include <memory>
#include <cstdio> // FILE, fopen, fclose, fputs

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

// 自定义删除器：一个接收 T* 的可调用对象，用来替代默认的 delete。
// 删除器不一定是"删除"内存的函数——它可以做任何清理工作（关闭文件、释放连接等），
// 可以是普通函数、函数对象或 lambda。shared_ptr 会在引用计数归零时调用它。
void my_delete(int* ptr) {
	cout << "my_delete: 释放自定义删除器管理的 int" << endl;
	delete ptr; // 这里仍然可以用 delete，因为该资源就是 new 出来的
}

int main() {
	// 可以用 new 返回的指针来初始化智能指针
	// 接收指针参数的智能指针构造函数是 explicit 的，所以不能将一个内置指针隐式转换为一个智能指针，必须使用初始化形式
	shared_ptr<int> p1(new int(1024));





	// 一个初始化智能指针的普通指针必须指向动态内存，因为智能指针默认使用 delete 释放它所关联的对象
	// 我们可以将智能指针绑定到一个指向其他类型的资源的指针上，但是这么做，必须提供自己的操作来替代 delete

	// 形式一：具名函数作删除器（上面注释中的 ? 处填 my_delete）
	shared_ptr<int> p2(new int(1024), my_delete);
	cout << "*p2 = " << *p2 << endl;

	// 形式二：lambda 作删除器（最常见的写法）
	shared_ptr<int> p3(new int(2048), [](int* ptr) {
		cout << "lambda 删除器被调用" << endl;
		delete ptr;
	});
	cout << "*p3 = " << *p3 << endl;

	// 形式三：管理"非内存资源"的经典例子——文件句柄
	// shared_ptr 管理的不是 new 出来的内存，而是一个 FILE*；
	// 引用计数归零时自动调用 fclose 而不是 delete
	{
		shared_ptr<FILE> pf(fopen("12_1_3_deleter_demo.txt", "w"), fclose);
		if (pf) {
			fputs("custom deleter demo\n", pf.get());
			cout << "文件已写入，离开作用域时将自动 fclose" << endl;
		}
	} // pf 离开作用域，fclose 被自动调用
	cout << "文件句柄已自动关闭" << endl;





	// 智能指针类型定义了一个 get 函数，它返回一个内置指针，使用get 返回的代码不能 delete 此指针
	shared_ptr<int> p(new int(42));
	int* q = p.get();// 要正确使用，不要让它管理的内存被释放
	{
		// 永远不要用 get 初始化的另一个智能指针，或者为另一个智能指针赋值
		shared_ptr<int>(q);
	} // 程序块结束，q被销毁，它所指向的内存已被释放
	//int foo = *p; // p 指向的内存已经被释放了！




	// 可以使用 reset 来将一个新的指针赋予一个 shared_ptr，与赋值类似，reset 会更新引用计数，如果需要会释放 p 指向的对象
	if (!p1.unique()) { // reset 经常与 unique 一起使用
		p1.reset(new int(1)); // 我们不是唯一的用户，分配新的拷贝
	}
	*p1 += 1; // 现在我们是我们引用对象的唯一用户了

	return 0;
} // main 结束，p2、p3 销毁时分别打印 my_delete 和 lambda 删除器的日志
