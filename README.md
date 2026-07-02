# learn_cpp_primer / 学习 《C++ Primer》

使用 **CMake** 管理构建，支持在 Visual Studio、CLion 以及 VSCode 中进行学习演练。

## 源文件约定

- 源文件可分散放在任意子目录中（如 `01/`、`02/`）。
- **每个源文件都是一个独立的、包含 `main` 函数的练习程序**，CMake 会自动为每个源文件生成一个可执行目标。
- 源文件名需在整个仓库中**唯一**，建议使用「章节号 + 主题」命名（如 `1.2iostream.cpp`），文件名中不要包含空格。
- 推荐使用 `.cpp` 扩展名；若使用 `.c`，CMake 也会按 C++ 编译。
- 新增源文件后，重新执行一次 CMake 配置即可被自动收集（已启用 `CONFIGURE_DEPENDS`）。

> 在程序返回前添加 `system("pause");` 可防止 Windows 下终端瞬间关闭。

## CMakeLists.txt 说明

根目录的 [CMakeLists.txt](CMakeLists.txt) 会递归收集所有 `.cpp/.cc/.cxx/.c` 源文件，并以「文件名（不含扩展名）」作为可执行目标名。所有可执行文件统一输出到 `build/bin/` 目录下。

> 说明：目标名中的点号等非字母数字字符会被替换为下划线（因为 Visual Studio 生成器对含点号的目标名处理有误）。例如 `1.2iostream.cpp` 对应的可执行文件为 `1_2iostream.exe`。

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
