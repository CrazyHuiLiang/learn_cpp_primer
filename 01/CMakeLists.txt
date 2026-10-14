# 章节 01：开始
# 目标命名规则：源文件名去掉最后一个扩展名后，所有非字母数字字符替换为下划线
#（Visual Studio 生成器对含点号的目标名处理有误）。

add_executable(1_1main             1.1main.cpp)
target_link_libraries(1_1main PRIVATE learn_cpp_primer_options)

add_executable(1_2iostream         1.2iostream.cpp)
target_link_libraries(1_2iostream PRIVATE learn_cpp_primer_options)

add_executable(1_4_1while_sum      1.4.1while_sum.cpp)
target_link_libraries(1_4_1while_sum PRIVATE learn_cpp_primer_options)

add_executable(1_4_2for_down       1.4.2for_down.cpp)
target_link_libraries(1_4_2for_down PRIVATE learn_cpp_primer_options)

add_executable(1_4_2for_sum        1.4.2for_sum.cpp)
target_link_libraries(1_4_2for_sum PRIVATE learn_cpp_primer_options)

add_executable(1_4_3sum_unknown    1.4.3sum_unknown.cpp)
target_link_libraries(1_4_3sum_unknown PRIVATE learn_cpp_primer_options)

add_executable(1_4_4count_dup      1.4.4count_dup.cpp)
target_link_libraries(1_4_4count_dup PRIVATE learn_cpp_primer_options)

add_executable(1_5_1sales_read     "1.5.1.1sales_read.cpp")
target_link_libraries(1_5_1sales_read PRIVATE learn_cpp_primer_options)

add_executable(1_5_1sales_add      "1.5.1.2sales_add.cpp")
target_link_libraries(1_5_1sales_add PRIVATE learn_cpp_primer_options)

add_executable(1_5_2sales_member   1.5.2sales_member.cpp)
target_link_libraries(1_5_2sales_member PRIVATE learn_cpp_primer_options)

add_executable(1_6bookstore        1.6bookstore.cpp)
target_link_libraries(1_6bookstore PRIVATE learn_cpp_primer_options)