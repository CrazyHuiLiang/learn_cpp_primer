# 章节 05：语句
# 目标命名规则：源文件名去掉最后一个扩展名后，所有非字母数字字符替换为下划线
#（Visual Studio 生成器对含点号的目标名处理有误）。

add_executable(5_3switch_vowel       5.3switch_vowel.cpp)
target_link_libraries(5_3switch_vowel PRIVATE learn_cpp_primer_options)

add_executable(5_4for_stmt           5.4for_stmt.cpp)
target_link_libraries(5_4for_stmt PRIVATE learn_cpp_primer_options)

add_executable(5_4while_stmt         5.4while_stmt.cpp)
target_link_libraries(5_4while_stmt PRIVATE learn_cpp_primer_options)

add_executable(5_5exception_classes  5.5exception_classes.cpp)
target_link_libraries(5_5exception_classes PRIVATE learn_cpp_primer_options)

add_executable(5_5try_catch          5.5try_catch.cpp)
target_link_libraries(5_5try_catch PRIVATE learn_cpp_primer_options)

add_executable(5_6break_continue     5.6break_continue.cpp)
target_link_libraries(5_6break_continue PRIVATE learn_cpp_primer_options)

add_executable(5_6goto               5.6goto.cpp)
target_link_libraries(5_6goto PRIVATE learn_cpp_primer_options)