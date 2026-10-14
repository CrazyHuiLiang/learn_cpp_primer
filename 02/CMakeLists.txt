# 章节 02：变量和基本类型
# 目标命名规则：源文件名去掉最后一个扩展名后，所有非字母数字字符替换为下划线
#（Visual Studio 生成器对含点号的目标名处理有误）。

add_executable(2_1arithmetic_types       2.1arithmetic_types.cpp)
target_link_libraries(2_1arithmetic_types PRIVATE learn_cpp_primer_options)

add_executable(2_2init_forms             2.2init_forms.cpp)
target_link_libraries(2_2init_forms PRIVATE learn_cpp_primer_options)

add_executable(2_3references             "2.3.1references.cpp")
target_link_libraries(2_3references PRIVATE learn_cpp_primer_options)

add_executable(2_3pointers               "2.3.2pointers.cpp")
target_link_libraries(2_3pointers PRIVATE learn_cpp_primer_options)

add_executable(2_4const                  2.4const.cpp)
target_link_libraries(2_4const PRIVATE learn_cpp_primer_options)

add_executable(2_4constexpr              "2.4constexpr.cpp")
target_link_libraries(2_4constexpr PRIVATE learn_cpp_primer_options)

add_executable(2_5aliases_auto_decltype  2.5aliases_auto_decltype.cpp)
target_link_libraries(2_5aliases_auto_decltype PRIVATE learn_cpp_primer_options)

add_executable(2_6sales_data_struct      2.6sales_data_struct.cpp)
target_link_libraries(2_6sales_data_struct PRIVATE learn_cpp_primer_options)