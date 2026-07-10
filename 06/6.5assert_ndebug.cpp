// ===========================================================================
//  《C++ Primer》6.5 节示例：assert 与 NDEBUG
// ---------------------------------------------------------------------------
//  要点：
//    - assert 宏（<cassert>）：运行时检查条件，失败则终止程序并输出诊断。
//        * 定义了 NDEBUG 宏后 assert 不再生效（编译期被替换为空）。
//        * assert 用于「不应发生」的内部逻辑检查，不应替代正常错误处理
//          （如用户输入校验、可预期的运行时错误应用异常/返回码处理）。
//    - 用 #ifndef NDEBUG 包裹自定义调试代码，与 assert 同步开关。
//    - 预定义变量：__func__（当前函数名）、__FILE__、__LINE__、__DATE__、
//      __TIME__ 可用于诊断信息。
//
//  说明：本仓库的 MSVC 默认 Release 配置会定义 NDEBUG，Debug 配置则不会。
//  如需观察 assert 生效，请用 Debug 构建；如需关闭 assert，定义 NDEBUG
//  （或切换到 Release）。
// ===========================================================================
#include <iostream>
#include <cassert>
#include <vector>

// 一个内部函数：要求 index 在 [0, size)
int at_index(const std::vector<int> &v, std::size_t index)
{
    // 不应发生的前置条件：用 assert
    assert(index < v.size() && "index out of range");

    // 自定义调试输出：与 assert 同步开关
    #ifndef NDEBUG
    std::cerr << "[debug] " << __func__ << " @ " << __FILE__ << ":" << __LINE__
              << "  index=" << index << std::endl;
    #endif

    return v[index];
}

int main()
{
    std::vector<int> v = {10, 20, 30};

    std::cout << at_index(v, 1) << std::endl;   // 正常：20

    // 预定义变量演示
    std::cout << "compiled on " << __DATE__ << " " << __TIME__ << std::endl;
    std::cout << "running in function: " << __func__ << std::endl;

    // 取消下面注释可观察 assert 失败（仅在未定义 NDEBUG 时终止程序）：
    // std::cout << at_index(v, 10) << std::endl;
    return 0;
}
