# 章节 08：IO类
# 目标命名规则：源文件名去掉最后一个扩展名后，所有非字母数字字符替换为下划线
#（Visual Studio 生成器对含点号的目标名处理有误）。

add_executable(8_1_2iostate             8.1.2iostate.cpp)
target_link_libraries(8_1_2iostate PRIVATE learn_cpp_primer_options)

add_executable(8_2fstream             8.2fstream.cpp)
target_link_libraries(8_2fstream PRIVATE learn_cpp_primer_options)

# 仅此目标：字面量按 UTF-8 写入 exe，与源码里的 SetConsoleOutputCP(CP_UTF8) 配对。
# 顶层只给了 /source-charset:utf-8，执行字符集回退到系统 ACP（中文 Windows 为 GBK），
# 其他章节沿用 GBK 以匹配传统 cmd 控制台，故这里单独覆盖，不改顶层。
# 用 /execution-charset 而非 /utf-8：后者等价于同时设置 source-charset，
# 会与顶层已有的 /source-charset:utf-8 重复，触发 MSVC 的 D9025 覆盖警告。
# GCC/Clang 的执行字符集默认就是 UTF-8，无需额外选项。
target_compile_options(8_2fstream PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/execution-charset:utf-8>
)

add_executable(8_3sstream             8.3sstream.cpp)
target_link_libraries(8_3sstream PRIVATE learn_cpp_primer_options)
