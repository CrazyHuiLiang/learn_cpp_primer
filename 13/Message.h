
/*
    资源管理并不是一个类需要定义自己的拷贝控制成员的唯一原因，一些类也需要拷贝控制成员的帮组来进行簿记工作或其他操作


    每个 Message 对象可以出现在多个 Folder 中，但是任意给定的 Message 的内容只有一个副本

    每个 Message 都会保存一个它所在 Folder 的指针的 set，同样，每个 Folder 都保存一个它包含的 Message 的指针的 set
    Message类会提供save和remove操作，来向一个给定Folder添加一条Message或是从中删除一条Message
*/


#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstddef>
#include <set>
#include <string>
#include "Folder.h"

class Message
{
    friend class Folder;
    friend void swap(Message&, Message&);

public:
    explicit Message(const std::string& str = "") : contents(str) {}

    // 拷贝控制成员，用来管理指向本 Message 的指针
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();

    // 从给定 Folder 集合中添加/删除 本Message
    void save(Folder&);
    void remove(Folder&);

    // 书中未提供，仅为演示观察：本 Message 位于多少个 Folder 中
    std::size_t folder_count() const { return folders.size(); }

private:
    std::string contents; // 实际消息文本
    std::set<Folder*> folders; // 包含 Message 的Folder

    // 将本消息添加到 m 的 folders 中
    void add_to_Folders(const Message&);

    // 从 folders 中的每个 Folder 中删除 Message
    void remove_from_Folders();
};

#endif
