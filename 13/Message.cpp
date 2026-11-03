#include "Message.h"

Message::Message(const Message& m) : contents(m.contents), folders(m.folders)
{
    add_to_Folders(m); // 将本消息添加到指向 m 的 Folder 中
}

Message& Message::operator=(const Message& rhs)
{
    remove_from_Folders();

    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);
    return *this;
}

Message::~Message()
{
    remove_from_Folders();
}

void swap(Message& lhs, Message& rhs)
{
    using std::swap;
    // 将每个消息的指针从它原本所在的 Folder 中删除
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);

    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);

    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}

void Message::save(Folder& f)
{
    folders.insert(&f);  // 将给定 Folder 添加到我们的 Folder 列表中
    f.addMsg(this);      // 将本 Message 添加到 f 的 Message 集合中
}

void Message::remove(Folder& f)
{
    folders.erase(&f);    // 将给定 Folder 从我们的 Folder 列表中删除
    f.remMsg(this);    // 将本消息从 Folder 中删除
}

void Message::add_to_Folders(const Message& m)
{
    for (const auto f : m.folders)
    {
        f->addMsg(this);
    }
}

void Message::remove_from_Folders()
{
    for (const auto f : folders)
    {
        f->remMsg(this);
    }
}
