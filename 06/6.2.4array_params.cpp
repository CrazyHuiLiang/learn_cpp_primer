// ===========================================================================
//  《C++ Primer》6.2 节示例：数组形参
// ---------------------------------------------------------------------------
//  要点：
//    - 数组不能按值传递，实际传递的是指向首元素的指针。以下三种形式等价：
//        void print(const int*);       // 指针形式
//        void print(const int[]);      // 不定长数组形式
//        void print(const int[10]);    // 「带长度」形式——长度被忽略
//      编译器把它们视作同一种类型：const int*。
//    - 管理数组形参长度的常见方式：
//        1) 用首尾指针（begin/end）；
//        2) 用标准库风格 [first, last) 区间；
//        3) 用数组引用形参（长度编码在类型里）。
//    - C 风格字符串形参：以 '\0' 结尾，函数靠检测 0 字符确定结束。
// ===========================================================================
#include <iostream>
#include <iterator>   // std::begin / std::end

// 三种等价形式：都是 const int*
void print_ptr(const int *p)        { std::cout << "print_ptr:       " << *p << std::endl; }
void print_arr(const int arr[])     { std::cout << "print_arr:       " << *arr << std::endl; }
void print_sized(const int arr[10]) { std::cout << "print_sized:     " << *arr << std::endl; }

// 用首尾指针遍历（标准库风格 [first, last)）
void print_range(const int *first, const int *last)
{
    std::cout << "print_range:     ";
    while (first != last) {
        std::cout << *first << ' ';
        ++first;
    }
    std::cout << std::endl;
}

// 数组引用形参：长度编码在类型里（这里固定长度 5）
void print_arr_ref(const int (&arr)[5])
{
    std::cout << "print_arr_ref:   ";
    for (int x : arr) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
}

// C 风格字符串形参：以 '\0' 结尾
void print_cstr(const char *cp)
{
    std::cout << "print_cstr:      \"";
    while (*cp != '\0') {       // 检测到 0 字符停止
        std::cout << *cp;
        ++cp;
    }
    std::cout << "\"" << std::endl;
}

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};

    // 三种等价形式都只看首元素
    print_ptr(arr);
    print_arr(arr);
    print_sized(arr);

    // 首尾指针
    print_range(std::begin(arr), std::end(arr));

    // 数组引用形参（长度必须严格匹配为 5）
    print_arr_ref(arr);

    // C 风格字符串
    print_cstr("hello");
    return 0;
}
