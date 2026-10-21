#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class HasPtr {
public:
	// 构造函数动态分配自己的 string
	HasPtr(const string& s = string()) : ps(new string(s)), i(0) {}
	// 对 ps 指向的 string，每个对象都有自己的拷贝
	HasPtr(const HasPtr &p): ps(new string(*p.ps)), i(p.i) {
		cout << "copy constructor called" << endl;
	}
	HasPtr& operator=(const HasPtr &);

	void printAddr() const {
		cout << ps << endl;
	}

	// 定义析构函数来释放 string
	~HasPtr() {
		delete ps;
	}

private:
	string *ps;
	int i;
};

/*
	赋值运算符通常结合了析构函数和构造函数的操作
		类似析构函数，赋值操作会销毁左侧运算对象的资源
		类似拷贝构造函数，赋值操作会从右侧运算对象拷贝数据
		注意，这些操作是以正确的顺序执行，而且应该是异常安全的，当异常发生时能将左侧运算对象置于一个有意义的状态
			
*/
HasPtr& HasPtr::operator=(const HasPtr& rhs) {

	/*
	delete ps;                // 先释放左侧对象指向的 string
	ps = new string(*rhs.ps); // 如果 rhs 和 *this 是同一个对象，我们就将从已释放的内存中拷贝数据！
	*/

	// 一个好的模式是，先将右侧运算对象拷贝到一个局部临时对象中，当拷贝完成后，
	// 销毁左侧运算对象的现有成员就是安全的。一旦左侧运算对象的资源被销毁，就
	// 只剩下将数据从临时对象拷贝到左侧运算对象的成员中了
	auto newp = new string(*rhs.ps);// 拷贝底层 string
	delete ps; // 释放旧内存

	ps = newp; // 从右侧运算符对象拷贝数据到本对象
	i = rhs.i;

	cout << "operator= called" << endl;
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
