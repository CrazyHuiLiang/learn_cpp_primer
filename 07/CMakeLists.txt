# 章节 07：类
# 目标命名规则：源文件名去掉最后一个扩展名后，所有非字母数字字符替换为下划线
#（Visual Studio 生成器对含点号的目标名处理有误）。

add_executable(7_1bookstore             7.1bookstore.cpp)
target_link_libraries(7_1bookstore PRIVATE learn_cpp_primer_options)

add_executable(7_1sales_data_add        7.1sales_data_add.cpp)
target_link_libraries(7_1sales_data_add PRIVATE learn_cpp_primer_options)

add_executable(7_1sales_data_basics     7.1sales_data_basics.cpp)
target_link_libraries(7_1sales_data_basics PRIVATE learn_cpp_primer_options)

add_executable(7_2encapsulation         7.2encapsulation.cpp)
target_link_libraries(7_2encapsulation PRIVATE learn_cpp_primer_options)

add_executable(7_3this_const            7.3this_const.cpp)
target_link_libraries(7_3this_const PRIVATE learn_cpp_primer_options)

add_executable(7_4scope                 7.4scope.cpp)
target_link_libraries(7_4scope PRIVATE learn_cpp_primer_options)

add_executable(7_5constructors          7.5constructors.cpp)
target_link_libraries(7_5constructors PRIVATE learn_cpp_primer_options)

add_executable(7_5delegating            7.5delegating.cpp)
target_link_libraries(7_5delegating PRIVATE learn_cpp_primer_options)

add_executable(7_6static_members        7.6static_members.cpp)
target_link_libraries(7_6static_members PRIVATE learn_cpp_primer_options)