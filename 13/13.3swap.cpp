#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;


class HasPtr {
	// 将 swap 定义为 friend，以便能访问 HasPtr 的数据成员
	friend void swap(HasPtr&, HasPtr&);
public:
	// 首先将 swap 定义为 friend，以便能访问 HasPtr 的 private的数据成员
	friend void swap(HasPtr&, HasPtr&);
	HasPtr(const string& s = string()) : ps(new string(s)), i(0), use(new std::size_t(1)) {}

	HasPtr(const HasPtr &p): ps(p.ps), i(p.i), use(p.use) {
		++*use;
		cout << "copy constructor called:" << *use << endl;
	}
	HasPtr& operator=(HasPtr);
	//HasPtr& operator=(const HasPtr&);

	void printAddr() const {
		cout << "ps:" << ps << " use="<< use << endl;
	}

	~HasPtr() {
		cout << "destructor called:" << *use << endl;
		if (--*use == 0) {
			delete ps;
			delete use;
			cout << "delete dynamic mamory" << endl;
		}
	}

private:
	string *ps;
	int i;
	std::size_t* use;// 用来记录有多少个对象共享 *ps 的成员
};








// 由于 swap 的存在就是为了优化代码，我们将其声明为 inline 函数
// 与拷贝控制成员不同，swap 并不是必要的，但是对于分配资源的类，定义 swap 可能是一种很重要的优化手段
inline void swap(HasPtr& lhs, HasPtr& rhs) {
	cout << "swap called" << endl;
	using std::swap;
	// 这里有一个微妙之处，这里应该使用 swap 的写法，而不是 std::swap，
	// 这样在对应的被交换的类型有定义 swap 函数时，优先使用对应类型自己定义的
	// 每个 swap 调用应该都是未加限定的，如果没有特定的 swap 版本，则会使用 std 中的版本（假定作用域中有 using 声明）
	swap(lhs.ps, rhs.ps); // 交换指针，而不是 string 数据
	swap(lhs.use, rhs.use); // 交换指针，而不是 string 数据
	swap(lhs.i, rhs.i); // 交换 int 成员
}

/*
HasPtr& HasPtr::operator=(const HasPtr& rhs) {
	++*rhs.use; // 递增右侧运算对象的引用计数
	if (--*use == 0) { // 然后递减本对象的引用计数
		delete ps; // 如果没有其他用户，则释放本对象分配的成员
		delete use;
	}
	ps = rhs.ps;
	i = rhs.i;
	use = rhs.use;
	return *this; // 返回本对象
}
*/

// 定义 swap 的类通常用 swap 来定义它们的赋值运算符
// 这些运算符使用了一种名为拷贝并交换的技术（copy and swap）
// 注意 rhs 是按值传递的，意味着 HasPtr 的拷贝构造函数，这种技术将左侧运算对象与右侧运算对象的一个副本进行交换
// 这个技术的有趣之处是它自动处理了自赋值情况且天然就是异常安全的。它通过在改变左侧运算对象之前拷贝右侧运算对象保证了自赋值的正确
// 这与我们在原来的赋值运算符中使用的方法是一致的
HasPtr& HasPtr::operator=(HasPtr rhs) {
	cout << "operator= called" << endl;
	// 交换左侧运算对象和局部变量的 rhs 的内容
	swap(*this, rhs); // rhs 现在指向本对象曾经使用的内存
	return *this; // rhs 被销毁，从而 delete 了 rhs 中的指针
}








int main() {

	HasPtr ptr1("ptr1");
	HasPtr ptr3;
	ptr3 = ptr1;
	
	ptr1.printAddr();
	ptr3.printAddr();
	cout << "ptr1 和 ptr3 的 ps 地址一致说明拷贝赋值运算符的行为是 ptr3 复制了 ptr1 的 ps 的地址" << endl;

	HasPtr ptr2(ptr1);
	ptr2.printAddr();


	return 0;
}
