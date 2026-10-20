# 章节 13：拷贝控制
# 目标命名规则：源文件名去掉最后一个扩展名后，所有非字母数字字符替换为下划线
#（Visual Studio 生成器对含点号的目标名处理有误）。

add_executable(13_1_1copy_constructor             13.1.1copy_constructor.cpp)
target_link_libraries(13_1_1copy_constructor PRIVATE learn_cpp_primer_options)

add_executable(13_1_2copy_assignment_operator     13.1.2copy_assignment_operator.cpp)
target_link_libraries(13_1_2copy_assignment_operator PRIVATE learn_cpp_primer_options)

add_executable(13_1_3destructor                   13.1.3destructor.cpp)
target_link_libraries(13_1_3destructor PRIVATE learn_cpp_primer_options)

add_executable(13_1_4rule35                   13.1.4rule35.cpp)
target_link_libraries(13_1_4rule35 PRIVATE learn_cpp_primer_options)

add_executable(13_1_5default                   13.1.5default.cpp)
target_link_libraries(13_1_5default PRIVATE learn_cpp_primer_options)







