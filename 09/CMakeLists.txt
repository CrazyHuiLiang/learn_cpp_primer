# 章节 09：顺序容器
# 目标命名规则：源文件名去掉最后一个扩展名后，所有非字母数字字符替换为下划线
#（Visual Studio 生成器对含点号的目标名处理有误）。

add_executable(9_2container             9.2container.cpp)
target_link_libraries(9_2container PRIVATE learn_cpp_primer_options)
