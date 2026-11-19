/*
    C++ Primer 13.5 动态内存管理类

    实现标准库 vector 类的一个简化版本，不使用模板，我们的类只使用 string，命名为 StrVec
*/
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cstddef>
#include <utility>

using std::pair;
using std::string;
using std::cout;
using std::endl;
using std::allocator;
using std::uninitialized_copy;


class StrVec
{
    public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {} // 指针成员置空，allocator 成员进行默认初始化
    StrVec(const StrVec&);  // 拷贝构造函数
    StrVec &operator=(const StrVec&); // 拷贝赋值运算符
     ~StrVec();

    void push_back(const string&);
    std::size_t size() const { return first_free - elements; }
    std::size_t capacity() const { return cap - elements; }
    string* begin() const { return elements; }
    string*end() const { return first_free; }

private:
    static allocator<string> alloc; // 分配元素
    string *elements;   // 指向数组首元素的指针
    string *first_free; // 指向数组首元素的指针
    string *cap;        // 指向数组尾后位置的指针

    // 被添加元素的函数所用
    void chk_n_alloc() { if (size() == capacity()) reallocate(); }
    pair<string*, string*> alloc_n_copy(const string*, const string*); // 工具函数，被拷贝构造函数、赋值运算符和析构函数所使用
    void free();    // 销毁元素并释放内存
    void reallocate(); // 获得更多内存并拷贝已有元素
};

// 静态成员的类外定义
allocator<string> StrVec::alloc;

void StrVec::push_back(const string& s) {
    chk_n_alloc(); // 确保有空间容纳新元素
    alloc.construct(first_free++, s); // 在 first_free 指向的元素中构造 s 的副本
}

pair<string*, string*> StrVec::alloc_n_copy(const string *b, const string *e) {
    // 分配空间保存给定范围中的元素
    auto data = alloc.allocate(e - b);
    // 初始化并返回一个 pair，该 pair 由 data 和 uninitialized_copy 的返回值构成
    return { data,  uninitialized_copy(b, e, data) };
}

void StrVec::free()
{
    if (elements)
    {
        // 先逆序销毁旧元素
        for (auto p=first_free; p!=elements;)
        {
            alloc.destroy(--p);
        }
        // 然后释放自己分配的内存空间
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec &s)
{
    // 调用 allloc_n_copy 分配空间以容纳与 s 中一样多个元素
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec &StrVec::operator=(const StrVec &rhs)
{
    // 调用 alloc_n_copy 分配内存，大小与 rhs 中元素占用空间一样多
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

/*
 * 为一个 StrVec 重新分配内存会引起从就内存空间到新内存空间逐个拷贝 string
 * 在重新分配内存空间时，如果我们能避免分配和释放 string 的额外开销，StrVec 的性能会好得多
 *
 * 通过使用新标准引入的两种机制，可以避免 string 的拷贝
 * 1. 是有些类支持移动构造函数，移动构造函数通常是将资源从给定对象“移动”而不是拷贝到正在创建的对象，而且我们知道标准库保证移动后源string仍然保持一个有效的、可析构的状态
 * 2. 使用 move 标准库函数，move 函数定义在 utility 头文件中
 */
void StrVec::reallocate()
{
    // 我们将分配当前大小两倍的内存空间
    auto newcapacity = size() ? 2 * size() : 1;
    // 分配新内存
    auto newdata = alloc.allocate(newcapacity);
    // 将数据从旧内存移动到新内存
    auto dest = newdata;
    auto elem = elements;
    for (std::size_t i = 0; i != size(); ++i) alloc.construct(dest++, std::move(*elem++)); // 调用 move 返回的结构会领 construct 使用 string 的移动构造函数，这些 string 管理的内存将不会被拷贝，相反，我们构造的每个 string 都会从 elem 指向的 string 那里接管内存的所有权
    // 一旦我们移动完元素就释放旧内存空间
    free();
    // 更新我们的数据结构，执行新元素
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}


int main() {

    StrVec v;
    v.push_back("1");
    v.push_back("2");
    v.push_back("3");
    for (auto item : v) {
        cout << item << endl;
    }
    return 0;
}
