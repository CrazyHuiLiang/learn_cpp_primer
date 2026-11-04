# 章节 08：IO类
# 目标命名规则：源文件名去掉最后一个扩展名后，所有非字母数字字符替换为下划线
#（Visual Studio 生成器对含点号的目标名处理有误）。

add_executable(8_1_2iostate             8.1.2iostate.cpp)
target_link_libraries(8_1_2iostate PRIVATE learn_cpp_primer_options)
