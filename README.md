# learn_cpp_primer / 学习 《C++ Primer》

使用 **CMake** 管理构建，支持在 Visual Studio、CLion 以及 VSCode 中进行学习演练。

## 源文件约定

- 练习源文件按章节放在 `01` / `02` / … / `07` 各自的子目录下。
- **每个源文件都是一个独立的、包含 `main` 函数的练习程序**，每个 `.cpp` 在所属章节的 `CMakeLists.txt` 中显式登记为一个可执行目标。
- 源文件名需在整个仓库中**唯一**，建议使用「章节号 + 主题」命名（如 `1.2iostream.cpp`），文件名中不要包含空格。
- 推荐使用 `.cpp` 扩展名。

> 在程序返回前添加 `system("pause");` 可防止 Windows 下终端瞬间关闭。

## CMakeLists.txt 说明

仓库采用「顶层入口 + 每章节子配置」的两层 CMake 结构：

- 顶层 [CMakeLists.txt](CMakeLists.txt) 只承担项目级设置：C++17、统一输出目录 `build/bin/`、把 `include/` 头目录与跨编译器编译选项集中到一个 INTERFACE 库 `learn_cpp_primer_options` 中，最后用 `add_subdirectory` 串起 `01` ~ `07` 七个章节。
- 每个章节目录下的 `CMakeLists.txt`（如 [01/CMakeLists.txt](01/CMakeLists.txt)）对该章节内的每个 `.cpp` 显式 `add_executable`，并通过 `target_link_libraries(<name> PRIVATE learn_cpp_primer_options)` 继承公共设置。

**新增练习时**，在所属章节的 `CMakeLists.txt` 中追加两行：

```cmake
add_executable(<净化目标名> <源文件名>)
target_link_libraries(<净化目标名> PRIVATE learn_cpp_primer_options)
```

> 说明：目标名采用「源文件去扩展名 + 非字母数字字符替换为下划线」的规则（Visual Studio 生成器对含点号的目标名处理有误）。例如 `1.2iostream.cpp` 对应的可执行文件为 `1_2iostream.exe`，所有章节的可执行文件统一输出到 `build/bin/` 目录下。

也可以只构建单个章节：

```bash
cmake -B build -S 01        # 只构建第 1 章
cmake --build build
```

## 在 Visual Studio 中使用

1. 打开 Visual Studio → 「打开本地文件夹」→ 选择本仓库根目录。
2. VS 会自动识别 CMake 项目并完成配置（首次可能需要稍等）。
3. 在上方工具栏选择要运行的「启动项」（即某个源文件对应的目标），按 F5 调试 / Ctrl+F5 运行。
4. 可在 `CMakeSettings.json`（菜单 项目 → CMake 设置）中切换 Debug/Release 及生成器。

## 在 CLion 中使用

1. 「Open」→ 选择本仓库根目录，CLion 会自动识别 `CMakeLists.txt`。
2. 选择工具链（MinGW/MSVC/WSL 等）后自动完成配置。
3. 右上角选择要运行的源文件目标，点击运行 / 调试按钮即可。

## 在 VSCode 中使用（可选）

推荐安装 **CMake Tools** 扩展：

1. `Ctrl+Shift+P` → `CMake: Configure` 完成配置。
2. 在底部状态栏选择「启动目标」与「构建类型」，点击运行 / 调试。

也可以在终端手动构建：

```bash
cmake -B build -S .
cmake --build build
# 运行某个练习（Windows）
./build/bin/Debug/1_2iostream.exe
```
