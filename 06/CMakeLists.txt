# 章节 06：函数
# 目标命名规则：源文件名去掉最后一个扩展名后，所有非字母数字字符替换为下划线
#（Visual Studio 生成器对含点号的目标名处理有误）。

add_executable(6_2_1pass_by_value          6.2.1pass_by_value.cpp)
target_link_libraries(6_2_1pass_by_value PRIVATE learn_cpp_primer_options)

add_executable(6_2_2pass_by_reference      6.2.2pass_by_reference.cpp)
target_link_libraries(6_2_2pass_by_reference PRIVATE learn_cpp_primer_options)

add_executable(6_2_3const_reference        6.2.3const_reference.cpp)
target_link_libraries(6_2_3const_reference PRIVATE learn_cpp_primer_options)

add_executable(6_2_4array_params           6.2.4array_params.cpp)
target_link_libraries(6_2_4array_params PRIVATE learn_cpp_primer_options)

add_executable(6_2_5main_args              6.2.5main_args.cpp)
target_link_libraries(6_2_5main_args PRIVATE learn_cpp_primer_options)

add_executable(6_2_6initializer_list              6.2.6initializer_list.cpp)
target_link_libraries(6_2_6initializer_list PRIVATE learn_cpp_primer_options)

add_executable(6_3recursion              6.3recursion.cpp)
target_link_libraries(6_3recursion PRIVATE learn_cpp_primer_options)

add_executable(6_3return                 6.3return.cpp)
target_link_libraries(6_3return PRIVATE learn_cpp_primer_options)

add_executable(6_4overload               6.4overload.cpp)
target_link_libraries(6_4overload PRIVATE learn_cpp_primer_options)

add_executable(6_5assert_ndebug          6.5assert_ndebug.cpp)
target_link_libraries(6_5assert_ndebug PRIVATE learn_cpp_primer_options)

add_executable(6_5constexpr_inline       6.5constexpr_inline.cpp)
target_link_libraries(6_5constexpr_inline PRIVATE learn_cpp_primer_options)

add_executable(6_5default_arguments      6.5default_arguments.cpp)
target_link_libraries(6_5default_arguments PRIVATE learn_cpp_primer_options)

add_executable(6_6function_pointer       6.6function_pointer.cpp)
target_link_libraries(6_6function_pointer PRIVATE learn_cpp_primer_options)