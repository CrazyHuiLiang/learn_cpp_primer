cmake_minimum_required(VERSION 3.15)

project(learn_cpp_primer LANGUAGES CXX)

# C++ 标准：C++ Primer 练习使用现代 C++ 特性，统一设置为 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 所有可执行文件统一输出到 build/bin 下，便于查找与调试
# （Visual Studio 等多配置生成器会自动加上 Debug/Release 子目录）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# 公共设置集中到 INTERFACE 库：include/ 公共头、跨编译器的警告与调试信息。
# 章节内每个目标只需 target_link_libraries(<name> PRIVATE learn_cpp_primer_options)
# 即可继承全部公共属性，避免在每个目标上重复写 target_*。
add_library(learn_cpp_primer_options INTERFACE)

# 把 include/ 目录加入头文件搜索路径，便于源文件 #include "Sales_item.h"
target_include_directories(learn_cpp_primer_options INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# 不同编译器下的警告与调试信息选项
# MSVC：用 /source-charset:utf-8 让源文件按 UTF-8 读取（中文注释/字面量解析正确），
# 但不强制执行字符集——这样字符串字面量沿用系统默认代码页（中文 Windows 为 GBK/936），
# 与 VS 调试时弹出的传统 cmd 控制台（GBK）匹配，避免中文输出乱码。
# 若改开 Windows 的"Beta: 使用 Unicode UTF-8 …"系统选项，可换回 /utf-8。
target_compile_options(learn_cpp_primer_options INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /source-charset:utf-8>
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -g>
)

# 各章节子配置：每个章节目录下都有自己的 CMakeLists.txt，对该章节内的 .cpp
# 显式 add_executable，并由章节内通过 PRIVATE 链接复用上面的公共设置。
add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)
add_subdirectory(04)
add_subdirectory(05)
add_subdirectory(06)
add_subdirectory(07)
add_subdirectory(13)
