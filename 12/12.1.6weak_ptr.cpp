#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::string;
using std::initializer_list;
using std::vector;
using std::size_t;

class StrBlobPtr;

class StrBlob {
	friend class StrBlobPtr;
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

	// 可以借用 StrBlobPtr 实现迭代器
	// 注意：StrBlobPtr 在此处还是不完整类型，只能声明，定义必须放到 StrBlobPtr 类定义之后
	// 且必须按值返回：返回引用会指向已销毁的临时对象（悬垂引用）
	StrBlobPtr begin();
	StrBlobPtr end();

private:
	// 实现一个新的集合类型的最简单方法是使用某个标准库容器来管理元素。采用这种方法，我们可以借助标准库类型来管理元素所使用的内存空间
	shared_ptr<vector<string>> data;
	// 如果 data[i] 不合法，抛出一个异常
	void check(size_type i, const string& msg) const;
};

StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}
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


class StrBlobPtr {
public:
	StrBlobPtr(): curr(0) {}
	StrBlobPtr(const StrBlob &a, size_t sz = 0): wptr(a.data), curr(sz) {}
	string& deref() const;
	StrBlobPtr& incr(); // 前缀递增
private:
	weak_ptr<vector<string>> wptr; // 指向 StrBlob 的 data
	std::size_t curr; // 在数组中的当前位置
	shared_ptr<vector<string>> check(std::size_t, const string&) const; // 检查访问的下标元素是否有效，成功返回指向 vector 的 shared_ptr
};

// 现在 StrBlobPtr 已是完整类型，可以在这里定义 StrBlob 的 begin/end
StrBlobPtr StrBlob::begin() {
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end() {
	return StrBlobPtr(*this, data->size());
}

shared_ptr<vector<string>> StrBlobPtr::check(std::size_t i, const string& msg) const {
	auto ret = wptr.lock();
	if (!ret) throw std::runtime_error("unbound StrBlobPtr");
	if (i >= ret->size()) throw std::out_of_range(msg);
	return ret;
}
string& StrBlobPtr::deref() const {
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}
StrBlobPtr& StrBlobPtr::incr() {
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

int main() {
	auto p = make_shared<int>(__LINE__);
	// 创建一个 weak_ptr 要用一个 shared_ptr
	weak_ptr<int> wp(p);

	// wp 不会改变 p 的引用计数，wp 指向的对象可能被释放掉
	// 由于对象可能不存在，我们不能使用 weak_ptr 直接访问对象，而必须调用 lock 函数检查 weak_ptr 指向的对象是否存在
	if (shared_ptr<int> np = wp.lock()) { // 如果存在，返回一个指向共享对象的 shared_ptr
		cout << *np << endl;
		//cout << *wp << endl; // 会报错，wp 不支持解引用操作
	}

	StrBlob lines;
	string temp;
	cout << "请输入若干单词（Ctrl+Z + 回车结束输入）：" << endl;
	while (std::cin >> temp) {
		lines.push_back(temp);
	}

	StrBlobPtr begin = lines.begin();
	for (StrBlob::size_type i = 0; i < lines.size(); i++) {
		cout << begin.deref() << endl;
		begin.incr();
	}

	return 0;
}
