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
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {
        cout << "构造函数" << endl;
    }
    StrVec(const StrVec&);
    StrVec &operator=(const StrVec&);

    StrVec(StrVec &&) noexcept;            // 移动操作不应该抛出任何异常
    StrVec &operator=(StrVec &&) noexcept;

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
    cout << "拷贝构造" << endl;
    // 调用 allloc_n_copy 分配空间以容纳与 s 中一样多个元素
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec &StrVec::operator=(const StrVec &rhs)
{
    cout << "拷贝赋值" << endl;
    // 调用 alloc_n_copy 分配内存，大小与 rhs 中元素占用空间一样多
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

/*
    与拷贝构造函数不同，移动构造函数不分配任何新内存，它接管给定的 StrVec 中的内存
    在接管内存之后，它将给定对象中的指针都置为 nullptr，这样就完成了从给定对象的移动操作，此对象将继续存在
    最终，移后源对象会被销毁，意味着将在其上运行析构函数。
*/
StrVec::StrVec(StrVec &&s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    cout << "移动构造" << endl;
    // 令 s 进入这样的状态：对其运行析构函数是安全的
    s.elements = s.first_free = s.cap = nullptr;
    // StrVec 的析构函数在 first_free 上调用 deallocate，如果我们忘记改变 s.first_free，则销毁移后源对象就会释放我们刚刚移动的内存
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
    cout << "移动赋值" << endl;
    // 直接检测自赋值，如果左右侧对象指向相同对象，我们不需要做任何事情
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        // 将 rhs 置于可析构状态
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

StrVec::~StrVec() { free(); }

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
    cout << "reallocate" << endl;
    // 我们将分配当前大小两倍的内存空间
    auto newcapacity = size() ? 2 * size() : 1;
    // 分配新内存
    auto newdata = alloc.allocate(newcapacity);
    // 将数据从旧内存移动到新内存
    auto dest = newdata;
    auto elem = elements;


    //for (std::size_t i = 0; i != size(); ++i) alloc.construct(dest++, std::move(*elem++)); // 调用 move 返回的结构会领 construct 使用 string 的移动构造函数，这些 string 管理的内存将不会被拷贝，相反，我们构造的每个 string 都会从 elem 指向的 string 那里接管内存的所有权
    // 移动元素，使用移动迭代器，比循环更简单
    auto last = uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), newdata);

    // 一旦我们移动完元素就释放旧内存空间
    free();
    // 更新我们的数据结构，执行新元素
    elements = newdata;
    //first_free = dest;
    first_free = last;
    cap = elements + newcapacity;
}


StrVec getVec() {
    StrVec v1; // 构造函数
    return v1; // 移动构造
}


int main() {

    int i = 42;

    int &r = i;
    //int &&rr = i;         // 右值引用不能绑定到左值

    //int &r2 = i * 42;     // 左值引用也不能绑定到右值
    int &&rr1 = i * 42;

    const int &r3 = i * 42; // 可以将一个 const 的引用绑定到一个右值，这是 C++ 设计时特意加入的特性，目的是让函数能够通过 const T& 参数接受任意实参（左值或右值），而无需为重载两个版本

    //int &&rr2 = rr1;      // 变量表达式都是左值，带来的结果就是我们不能将一个右值引用绑定到一个右值引用类型的变量上

    /*
        我们可以显式地将一个左值转换为对应的右值引用类型。
        通过调用 move 的标准库函数来获得绑定到左值上的右值引用，此函数定义在 utility 中
        move 调用告诉编译器：我们有一个左值，但我们希望像一个右值一样处理它
    */
    // 调用 move 就意味着承诺，除了对 rr1 赋值或销毁它外，我们将不再使用它。在调用 move 之后，我们不能对移后的源对象的值做任何假设
    int &&rr2 = std::move(rr1);


    StrVec v1, v2;
    v1 = v2; // v2 是左值，使用拷贝赋值
    // getVec 调用的结果此表达式是一个右值。此情况下，两种赋值运算符都是可行的；将 getVec的结果绑定到两个运算符的参数都是允许的。调用拷贝赋值运算符需要进行一次到 const 的转换，而 StrVec&& 则是精确匹配，因此使用移动赋值运算符。
    v2 = getVec(); // getVec 是一个右值，使用移动赋值

    return 0;
}
