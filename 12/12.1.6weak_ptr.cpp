#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;

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

	return 0;
}
