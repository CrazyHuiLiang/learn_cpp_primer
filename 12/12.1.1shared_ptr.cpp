#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <initializer_list>
#include <stdexcept>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::shared_ptr;
using std::initializer_list;
using std::make_shared;

class StrBlob {
public:
	typedef std::vector<string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<string> il);
	size_type size() const {
		return data->size();
	}
	bool empty() const {
		return data->empty();
	}
	// 添加和删除元素
	void push_back(const string& t) {
		data->push_back(t);
	}
	void pop_back();

	// 元素访问
	string& front();
	string& back();

private:
	// 实现一个新的集合类型的最简单方法是使用某个标准库容器来管理元素。采用这种方法，我们可以借助标准库类型来管理元素所使用的内存空间
	std::shared_ptr<vector<string>> data;
	// 如果 data[i] 不合法，抛出一个异常
	void check(size_type i, const string &msg) const;
};

StrBlob::StrBlob(): data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il): data(make_shared<vector<string>>(il)){}
void StrBlob::check(size_type i, const string& msg) const {
	if (i >= data->size()) {
		throw std::out_of_range(msg);
	}
}
string& StrBlob::front() {
	check(0, "front on empty StrBlob");
	return data->front();
}
string& StrBlob::back() {
	check(0, "back on empty StrBlob");
	return data->back();
}
void StrBlob::pop_back() {
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}








int main() {
	// make_shared 用其参数来构造给定类型的对象。
	shared_ptr<int> p3 = make_shared<int>(42);
	cout << *p3 << endl; // 42
	shared_ptr<string> p4 = make_shared<string>(10, '9');
	cout << *p4 << endl; // 999999999


	// 当进行拷贝或赋值操作时，每个 shared_ptr 都会记录有多少个其他 shared_ptr 指向相同的对象
	// 我们可以认为每个shared_ptr 都有一个关联的计数器，通常称其为引用计数，无论何时我们拷贝一个 shared_ptr，计数器都会递增
	// 局部的 shared_ptr 离开其作用域时，计数器就会递减，一旦一个 shared_ptr 的计数器变为0，它就会自动释放自己所管理的对象，它通过对象的析构函数完成销毁工作
	// shared_ptr 的析构函数会递减它所指向的对象的引用计数，如果计数变为 0，shared_ptr 的析构对象就会销毁对象，并释放它占用的内存
	auto p = make_shared<int>(42);
	auto q(p); // p 和 q 指向相同对象


	StrBlob b1;
	{
		StrBlob b2 = { "a", "an", "the" };
		// 默认拷贝赋值，会将b2的 data 这一智能指针的计数加一，b1的计数减一并释放，b1 和 b2 会共享同一份 data
		b1 = b2;
		
		// b2 向data添加了元素
		b2.push_back("about");
		// b1 也能看到
        cout << b1.size() << endl; // 4
        cout << b2.size() << endl; // 4
	}
	// b2 退出作用域，销毁一份引用计数后，b1 仍持有
    cout << b1.size() << endl; // 4
	return 0;
}