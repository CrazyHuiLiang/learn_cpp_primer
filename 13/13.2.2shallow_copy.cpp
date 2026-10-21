#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/*
	对于行为类似指针的类，我们需要为其定义拷贝构造函数和拷贝赋值运算符，来拷贝指针成员本身而不是它指向的 string
	我们的类仍需要自己的析构函数来释放 string 参数的构造函数分配的内存，但是析构函数不能单方面地释放关联的 string，
	只有最后一个引用 string 的对象销毁时才能释放string

	使用引用计数
		创建一个对象时，引用技术初始化为1
		拷贝构造函数不分配新的计数器，而是给拷贝给定对象的数据成员，包括计数器，拷贝构造函数递增共享的计数器，指出给定对象的状态被一个新用户所共享
		析构函数递减计数器，如果计数器变为0，则释放状态
		拷贝赋值运算符递增右侧运算符对象的计数器，递减左侧运算对象的计数器。如果左侧运算对象的计数器变为0，则必须销毁状态

		计数器放在哪里呢？
			一种方法是将计数器保存到动态内存中，当创建一个对象时，我们也分配一个新的计数器，当拷贝或赋值对象时，我们拷贝指向计数器的指针。
			这样，副本和原对象都会指向相同的计数器
**/
class HasPtr {
public:
	// 构造函数动态分配自己的 string 和新的计数器，将计数器置为1
	HasPtr(const string& s = string()) : ps(new string(s)), i(0), use(new std::size_t(1)) {}

	// 拷贝所有三个数据成员，并递增计数器
	HasPtr(const HasPtr &p): ps(p.ps), i(p.i), use(p.use) {
		++*use;
		cout << "copy constructor called" << endl;
	}
	HasPtr& operator=(const HasPtr &);

	void printAddr() const {
		cout << ps << endl;
	}

	// 析构函数应该递减引用计数，如果计数器变为0，释放ps和use指向的内存
	~HasPtr() {
		cout << "destructor called" << endl;
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

/*
	赋值运算符必须处理自赋值，我们通过线递增 rhs 中的计数，再递减左侧运算对象中的计数来实现这一点
		当两个对象相同时，在我们检查 use 时，计数器就已经被递增过了
*/
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


int main() {

	HasPtr ptr1("ptr1");
	HasPtr ptr2(ptr1);
	HasPtr ptr3;
	ptr3 = ptr1;
	
	ptr1.printAddr();
	ptr2.printAddr();
	ptr3.printAddr();

	return 0;
}
