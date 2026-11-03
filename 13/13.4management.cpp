/*
    C++ Primer 13.4 拷贝控制示例：Message / Folder

    本节核心：拷贝控制不只为"资源管理"，也为"簿记"——
    Message 与 Folder 通过裸指针互相登记，拷贝/赋值/析构/swap 都必须
    维护两侧簿记的一致性（Message 的 folders 集合 <-> Folder 的 messages 集合）。

    下面每一步执行一个拷贝控制操作，并输出两侧簿记数量以便核对。
*/

#include <iostream>
#include "Message.h"
#include "Folder.h"

using std::cout;
using std::endl;

int main() {
    // 注意声明顺序：Folder 先声明 → 先构造 → 后销毁（析构是构造的逆序）。
    // Message 析构时 remove_from_Folders() 需要访问这些 Folder 对象，而
    // Folder 目前没有自己的析构函数（练习 13.19），正确性依赖这个声明顺序约定：
    // 保证 Message 先于 Folder 销毁。
    Folder folder1, folder2;
    Message m1("message1"), m2("message2");

    // 1) save：同时写两侧簿记的公开接口 ——
    //    m1.folders 加入 &folder1，folder1.messages 加入 &m1。
    //    底层的 addMsg/remMsg 是单边操作，单独调用会破坏一致性，
    //    所以设为 private + friend，对外只暴露 save/remove。
    m1.save(folder1);
    m2.save(folder1);
    m2.save(folder2); // 一条 Message 可同时属于多个 Folder
    cout << "[save]      folder1: " << folder1.message_count()  // 预期 2
         << " msgs, folder2: " << folder2.message_count()       // 预期 1
         << " msgs, m2 在 " << m2.folder_count() << " 个 Folder" << endl;  // 预期 2

    // 2) 拷贝构造：合成拷贝是浅拷贝——只逐元素复制 set<Folder*>，
    //    副本不会被任何 Folder"认识"，两侧簿记即被破坏。
    //    自定义拷贝构造用 add_to_Folders 把 m3 登记进 m1 所在的每个 Folder。
    Message m3(m1);
    cout << "[拷贝构造]  folder1: " << folder1.message_count()  // 预期 3（m3 加入）
         << " msgs, m3 在 " << m3.folder_count() << " 个 Folder" << endl;  // 预期 1

    // 3) 拷贝赋值：顺序是"先注销旧的，再拷贝数据，最后登记新的"。
    //    m2 先从 folder1/folder2 中移除自己，再加入 m3 所在的 Folder（仅 folder1）。
    m2 = m3;
    cout << "[拷贝赋值]  folder1: " << folder1.message_count()  // 预期 3（m1,m2,m3）
         << " msgs, folder2: " << folder2.message_count()       // 预期 0（m2 已离开）
         << " msgs, m2 在 " << m2.folder_count() << " 个 Folder" << endl;  // 预期 1

    // 4) 自赋值安全：operator= 的 remove → 拷贝 → add 顺序使 m1 = m1 也正确
    //    （先从 folder1 注销，拷贝后重新登记）。
    //    借助引用绕过部分编译器对直接写 m1 = m1 的告警。
    Message& ref = m1;
    m1 = ref;
    cout << "[自赋值]    folder1: " << folder1.message_count()  // 预期 3（不变）
         << " msgs, m1 在 " << m1.folder_count() << " 个 Folder" << endl;  // 预期 1

    // 5) swap：不只交换 contents 和 folders，还要修正两侧 Folder 中
    //    持有的 Message 指针（先 remMsg，交换后再 addMsg）——
    //    当对象被外部按指针引用时，swap 必须"通知所有引用者"。
    swap(m1, m3);
    cout << "[swap]      folder1: " << folder1.message_count()  // 预期 3（集合内容不变）
         << " msgs, m1 在 " << m1.folder_count() << " 个 Folder" << endl;  // 预期 1

    // 6) remove：与 save 对称，两侧同时注销。
    m1.remove(folder1);
    cout << "[remove]    folder1: " << folder1.message_count()  // 预期 2（m2,m3）
         << " msgs, m1 在 " << m1.folder_count() << " 个 Folder" << endl;  // 预期 0

    // 作用域结束，析构顺序为构造的逆序：
    // m3、m2、m1 先销毁（各自 remove_from_Folders 把自己从 Folder 中注销），
    // 之后 folder2、folder1 才销毁，此时 messages 集合已空，无悬垂指针。
    cout << "done" << endl;
    return 0;
}
