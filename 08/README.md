# 8 IO库

C++ 语言不直接处理输入输出，而是通过一族定义在标准库中的类型来处理IO。
这些类型支持从设备读取数据、向设备写入数据的IO操作。
设备可以是文件、控制台窗口等。
还有一些类型允许内存IO，从 string 读取数据，向string写入数据。


## 8.1 IO类

标准库定义了一些 IO 类型，这些IO类型定义在三个独立的头文件中：

- iostream
	- istream,wistream 从流读取数据
	- ostream,wostream 向流写入数据
	- iostream,wiostream 读写流
- fstream
	- ifstream,wifstream 从文件读取数据
	- ofstream,wofstream 向文件写入数据
	- fstream,wfstream 读写文件
- sstream
	- istringstream,wistringstream
	- ostringstream,wostringstream
	- stringstream,wstringsteam

宽字符版本的类型和函数的名字以一个 w 开始，wcin、wcout 和 wcerr 分别是 cin、cout和cerr 的宽字符版对象

概念上，设备类型和字符大小都不会影响我们要执行的 IO 操作，例如我们可以用 >> 读取数据，不用管是从一个控制台窗口，还是一个文件，还是一个 string。这是通过继承机制实现的，
类型 ifstream 和 istringstream 都继承自 istream,因此我们可以像使用 istream 对象一样来使用 ifstream 和 istringstream 对象。

### 8.1.1 IO 对象无拷贝或赋值

我们不能拷贝或对 IO 对象赋值，因此我们也不能将形参或返回类型设置为流类型。
进行 IO 操作的函数通常以引用方式传递和返回流。读写一个 IO 对象会改变其状态，因此传递的和返回的引用不能是 const 的。

### 8.1.2 条件状态

IO 操作可能发生错误，IO 类定义了一些函数和标志可以帮助我们访问和操纵流的条件状态。


### 8.1.3 管理输出缓冲

每个输出流都管理一个缓冲区，用来保存程序读写的数据，文本串可能立即打印出来，也有可能被操作系统保存在缓冲区中，随后再打印。
导致缓冲区刷新的原因有很多：

- 程序正常结束，作为 mian 函数 return 操作的一部分，缓冲区刷新被执行
- 缓冲区满
- 使用操纵符 endl 显式刷新缓冲区
- 可以使用操纵符 unitbuf 设置流的内部状态，来清空缓冲区
- 一个输出流可能被关联到另一个流

IO 库中有两个类似的操纵符：

- flush 刷新缓冲区，但不输出任何额外的字符
- ends 向缓冲区插入一个空字符，然后刷新缓冲区

#### unibuf 操纵符

如果想在每次输出操作后都刷新缓冲区，我们可以使用 unitbuf 操纵符，它告诉流在接下来的每次写操作之后都进行一次 flush 操作。
而 nounitbuf 操纵符则重置流，使其恢复使用正常的系统管理的缓冲区刷新机制

#### 关联输入和输出流

当一个输入流被关联到一个输出流时，任何试图从输入流读取数据的操作都会先刷新关联的输出流。

交互式系统通常应该关联输入流和输出流，这意味着所有输出，包括用户提示信息，都会在读操作之前被打印出来。

tie 有两个重载的版本

- 一个不带参数的版本，返回指向输出流的指针；有查询的意思
- 一个接收指向 ostream 的指针，将自己关联到 ostream；是设置的意思


## 8.2 文件输入输出

- ifstream 从一个给定文件读取数据
- ofstream 从一个给定文件写入数据
- fstream  可以读写给定文件

我们可以用 IO 运算符 (`<<` 和 `>>`) 来读写文件
可以用 getline (定义在 string 头文件)从一个 ifstream 读取数据

fstream 中定义的类型还增加了一些新的成员

- 创建实例
	- fstream fstrm; 创建一个实例，没有绑定文件流
	- fstream fstrm(s); 创建一个实例，绑定名字为 s 的文件
	- fstream fstrm(s, mode); 创建一个实例，绑定名字为 s 的文件，按指定 mode 打开文件
- 打开关闭文件
	- fstrm.open(s) 打开名为 s 的文件
	- fstrm.open(s, mode) 按指定 mode 打开名为 s 的文件
	- fstrm.close() 关闭绑定的文件
	- fstrm.is_open() 是否成功打开且尚未关闭

如果调用 open 失败，failbit 会被置位，进行 open 是否成功的检测通常是一个好习惯；
对一个已经打开的文件流，再次调用 open 会失败，并导致 failbit 被置位；
为了将文件流关联到另一个文件，必须首先关闭已经关联的文件，一旦文件成功关闭，我们可以打开新的文件。
当一个 fstream 对象离开其作用域时，对象被销毁，close 会自动调用，与之关联的文件会自动关闭。


### 8.2.1 编码约定：为什么这个目标要单独设执行字符集

`8.2fstream.cpp` 是本仓库里唯一一个在编译期显式指定 **UTF-8 执行字符集**的目标。

顶层 `CMakeLists.txt` 只给了 MSVC 的 `/source-charset:utf-8`，**没有**给 `/execution-charset`，两者含义不同：

- `/source-charset:utf-8` —— 源文件按 UTF-8 **读取**，中文注释和字面量能正确解析
- 执行字符集未指定 —— 字面量按**系统 ACP**（中文 Windows 即 GBK/936）**写入** exe

这是刻意的设计：让输出匹配 VS 调试时弹出的传统 cmd 控制台（GBK）。其他章节都沿用这套约定。

而本练习调用了 `SetConsoleOutputCP(CP_UTF8)`，声明控制台按 UTF-8 解码。若不配套修改执行字符集，就会变成 **exe 发出 GBK 字节、控制台按 UTF-8 解码**，所有硬编码中文字面量乱码。因此 `08/CMakeLists.txt` 单独为它加了 `/execution-charset:utf-8`。

这两处设置是成对出现的，删掉任何一边都会重新乱码：

| 位置 | 设置 | 作用 |
| --- | --- | --- |
| `08/CMakeLists.txt` | `/execution-charset:utf-8` | 字面量以 UTF-8 写入 exe |
| `8.2fstream.cpp` | `SetConsoleOutputCP(CP_UTF8)` | 控制台按 UTF-8 解码 |

`SetConsoleOutputCP` 必须放在 `main` 的**第一条语句**、所有输出之前。否则先于它执行的那句错误提示（`请输入文件路径!`）会以 UTF-8 字节发给还是 GBK 的控制台，反而乱码。

> 这里用 `/execution-charset:utf-8` 而不是 `/utf-8`：后者等价于同时设置 source-charset，会与顶层已有的 `/source-charset:utf-8` 重复，触发 MSVC 的 D9025 覆盖警告。

#### 已知代价

程序把从文件读出的内容**原样透传**到控制台，不做编码转换。控制台切到 UTF-8 之后，**GBK/ANSI 编码的输入文件，其内容会显示乱码**，只有 UTF-8 或纯 ASCII 的输入文件才正常。这是选定方案的固有取舍，不是 bug。

写入 `.copy` 文件的内容同样是原始字节透传，不经过控制台代码页，因此不受本次编码设置影响。（注意 `.copy` 并不与输入文件逐字节相同——程序是用 `>>` 按空白切词后每词一行重新写出的，原有的换行与缩进结构不会保留。）


## 8.3 string 流

sstream 头文件定义了三个类型来支持内存IO

- istringstream 从 string 读取数据
- ostringstream 向 string 写入数据
- stringstream 既可以从 string 读取数据，也可以向 string 写入数据

头文件 sstream 中定义的类型都继承自我们已经使用过的 iostream 头文件中定义的类型，此外还增加了一些成员来管理与流相关联的 string。

- sstream strm; strm 是一个未绑定的 string 的 stringstream 对象
- sstream strm(s); 保存了 string s的一个拷贝
- strm.str() 返回 strm 所保存的 string 的拷贝
- strm.str(s) 将 string s 拷贝到 strm 中
