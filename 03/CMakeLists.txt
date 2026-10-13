# 章节 03：字符串、向量和数组
# 目标命名规则：源文件名去掉最后一个扩展名后，所有非字母数字字符替换为下划线
#（Visual Studio 生成器对含点号的目标名处理有误）。

add_executable(3_1using_decls        3.1using_decls.cpp)
target_link_libraries(3_1using_decls PRIVATE learn_cpp_primer_options)

add_executable(3_2string_io          3.2string_io.cpp)
target_link_libraries(3_2string_io PRIVATE learn_cpp_primer_options)

add_executable(3_2string_ops         3.2string_ops.cpp)
target_link_libraries(3_2string_ops PRIVATE learn_cpp_primer_options)

add_executable(3_2string_punct       3.2string_punct.cpp)
target_link_libraries(3_2string_punct PRIVATE learn_cpp_primer_options)

add_executable(3_3vector_basics      3.3vector_basics.cpp)
target_link_libraries(3_3vector_basics PRIVATE learn_cpp_primer_options)

add_executable(3_3vector_iter        3.3vector_iter.cpp)
target_link_libraries(3_3vector_iter PRIVATE learn_cpp_primer_options)

add_executable(3_4binary_search      3.4binary_search.cpp)
target_link_libraries(3_4binary_search PRIVATE learn_cpp_primer_options)

add_executable(3_5arrays             3.5arrays.cpp)
target_link_libraries(3_5arrays PRIVATE learn_cpp_primer_options)

add_executable(3_5cstrings           3.5cstrings.cpp)
target_link_libraries(3_5cstrings PRIVATE learn_cpp_primer_options)