#include <iostream>
#include <string>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;
using std::make_shared;
using std::allocator;

int main() {
	// new 有一些灵活性上的局限，其中一方面表现在它将内存分配和对象构造组合在一起，类似的 delete 将对象析构和内存释放组合在一起
	// 当需要一大块内存时，我们通常计划在这块内存上按需构造对象，我们希望将内存分配和对象构造分离，意味着我们可以分配大块内存，但只在真正需要时才真正执行对象创建操作
	// 标准库 allocator 类定义在头文件 memory 中，它帮助我们将内存分配和对象构造分离开来，它提供一种类型感知的内存分配方法，它分配的内存是原始的、未构造的
	// allocator 是一个模板，为了定义一个 allocator 对象，我们必须指明这个 allocator 可以分配的对象类型，当一个 allocator 对象分配内存时，它会根据给定的对象类型来确定恰当的内存大小和对齐位置
	allocator<string> alloc; // 可以分配 string 的 allocator 对象
	int n = 10;
	auto const partial = alloc.allocate(n); // 分配 n 个未初始化的 string

	// allocator 分配的内存是未构造的，construct 成员函数接受一个指针和零个或多个额外参数，在给定位置构造一个元素
	// 额外参数用来初始化构造对象，这些额外参数必须与构造的对象的类型相匹配的合法的初始化器
	// 还未构造对象的情况下就使用原始内存时错误的
	auto q = partial; // q 指向最后构造的元素之后的位置
	alloc.construct(q++); // *q 为空字符串
	cout << *(q-1) << endl;
	alloc.construct(q++, 10, 'c'); // *q 为 cccccccccc
	cout << *(q - 1) << endl;
	alloc.construct(q++, "hi"); // *q 为 hi
	cout << *(q - 1) << endl;


	// 当我们用完对象后，必须对每个构造的元素调用 destroy 来销毁它们。函数 destroy 接受一个指针，对指向的对象执行析构函数
	// 我们只能对真正构造了的元素进行 destroy 操作
	while (q != partial) {
		alloc.destroy(--q);
	}
	// 内存不再使用后可以归还给系统,传递给 deallocate 的大小参数必须与 调用 allocated 分配时提供的大小参数一样
	alloc.deallocate(partial, n);



	// 标准库还为 allocator 类定义了两个伴随算法，可以在未初始化内存中拷贝或填充对象
	allocator<int> alloci;
	auto const partiai = alloci.allocate(20); // 分配 20 个未初始化的 int
	vector<int> vi = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	auto q1 = std::uninitialized_copy(vi.begin(), vi.begin() + 5, partiai); // 使用 vi 的前5个元素填充 partiai 前五个位置，返回填充后的下一位置迭代器
	auto q2 = std::uninitialized_copy_n(vi.begin() + 5, 5, q1);             // 从 vi 的第5个位置后的元素，拿出5个跳充q1后面的位置
	auto q3 = std::uninitialized_fill_n(q2, 5, 43);						    // 向 q2 位置开始，向后使用值 43 填充5个位置
	std::uninitialized_fill(q3, q3 + 5, 53);								// 从 q3 位置开始，填充到 q3 + 5 的位置，值填充为 5，注意，这个函数没有返回值
	for (int i = 0; i < 20; i++) {
		cout << *(partiai+i) << endl;
	}

	return 0;
}
