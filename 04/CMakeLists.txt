# 章节 04：表达式
# 目标命名规则：源文件名去掉最后一个扩展名后，所有非字母数字字符替换为下划线
#（Visual Studio 生成器对含点号的目标名处理有误）。

add_executable(4_1arithmetic_ops     4.1arithmetic_ops.cpp)
target_link_libraries(4_1arithmetic_ops PRIVATE learn_cpp_primer_options)

add_executable(4_2logical_relational 4.2logical_relational.cpp)
target_link_libraries(4_2logical_relational PRIVATE learn_cpp_primer_options)

add_executable(4_3assignment         4.3assignment.cpp)
target_link_libraries(4_3assignment PRIVATE learn_cpp_primer_options)

add_executable(4_4incr_decr          4.4incr_decr.cpp)
target_link_libraries(4_4incr_decr PRIVATE learn_cpp_primer_options)

add_executable(4_5ternary            4.5ternary.cpp)
target_link_libraries(4_5ternary PRIVATE learn_cpp_primer_options)

add_executable(4_8bitwise_ops        4.8bitwise_ops.cpp)
target_link_libraries(4_8bitwise_ops PRIVATE learn_cpp_primer_options)

add_executable(4_9sizeof_cast        4.9sizeof_cast.cpp)
target_link_libraries(4_9sizeof_cast PRIVATE learn_cpp_primer_options)