cmake_minimum_required(VERSION 3.15)

project(learn_cpp_primer LANGUAGES CXX)

# C++ 标准：C++ Primer 练习使用现代 C++ 特性，统一设置为 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 所有可执行文件统一输出到 build/bin 下，便于查找与调试
# （Visual Studio 等多配置生成器会自动加上 Debug/Release 子目录）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# 自动递归收集所有练习源文件
# 约定：每个源文件都是独立的、包含 main 函数的练习程序
file(GLOB_RECURSE LEARN_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# 排除构建目录内的源文件（如 CMake 自动生成的 CMakeCXXCompilerId.cpp），
# 否则会与同名目标冲突
list(FILTER LEARN_SOURCES EXCLUDE REGEX "(/build/|/cmake-build-[^/]*/|/out/|/\\.vs/)")

# 为每个源文件创建一个独立的可执行目标
# 目标名取文件名（不含扩展名），要求整个仓库内文件名唯一（见 README）
foreach(SRC IN LISTS LEARN_SOURCES)
    # 取文件名（含扩展名）后，仅去掉最后一个扩展名
    get_filename_component(TARGET_NAME "${SRC}" NAME)
    string(REGEX REPLACE "\\.[^.]*$" "" TARGET_NAME "${TARGET_NAME}")
    # 净化目标名：Visual Studio 生成器对名字中的点号等字符处理有误
    # （如 "1.2iostream" 会被错误输出为 "1.exe"），统一替换为下划线
    string(REGEX REPLACE "[^a-zA-Z0-9_]" "_" TARGET_NAME "${TARGET_NAME}")

    # 仓库中可能存在扩展名为 .c 的 C++ 源文件，强制按 C++ 编译
    get_filename_component(SRC_EXT "${SRC}" EXT)
    if(SRC_EXT STREQUAL ".c")
        set_source_files_properties("${SRC}" PROPERTIES LANGUAGE CXX)
    endif()

    add_executable(${TARGET_NAME} "${SRC}")
    # 可执行文件名默认即为目标名（如 1_2iostream.exe）

    # 把 include/ 目录加入头文件搜索路径，便于源文件 #include "Sales_item.h"
    target_include_directories(${TARGET_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include")

    # 不同编译器下的警告与调试信息选项
    # MSVC：用 /source-charset:utf-8 让源文件按 UTF-8 读取（中文注释/字面量解析正确），
    # 但不强制执行字符集——这样字符串字面量沿用系统默认代码页（中文 Windows 为 GBK/936），
    # 与 VS 调试时弹出的传统 cmd 控制台（GBK）匹配，避免中文输出乱码。
    # 若改开 Windows 的“Beta: 使用 Unicode UTF-8 …”系统选项，可换回 /utf-8。
    target_compile_options(${TARGET_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /source-charset:utf-8>
        $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -g>
    )
endforeach()
