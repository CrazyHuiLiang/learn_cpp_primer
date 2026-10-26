# 章节 12：动态内存
# 目标命名规则：源文件名去掉最后一个扩展名后，所有非字母数字字符替换为下划线
#（Visual Studio 生成器对含点号的目标名处理有误）。

add_executable(12_1_1shared_ptr             12.1.1shared_ptr.cpp)
target_link_libraries(12_1_1shared_ptr PRIVATE learn_cpp_primer_options)

add_executable(12_1_2direct_memory_management             12.1.2direct_memory_management.cpp)
target_link_libraries(12_1_2direct_memory_management PRIVATE learn_cpp_primer_options)

add_executable(12_1_3shared_ptr_with_new             12.1.3shared_ptr_with_new.cpp)
target_link_libraries(12_1_3shared_ptr_with_new PRIVATE learn_cpp_primer_options)

