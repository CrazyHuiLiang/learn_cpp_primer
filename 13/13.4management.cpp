#include <iostream>
#include <set>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::set;


namespace
{

    class Folder;
    class Message
    {
        friend class Folder;
    public:
        explicit Message(const string &str = ""): contents(str) {}

        // 拷贝控制成员，用来管理指向本 Message 的指针
        Message(const Message&);
        Message& operator=(const Message&);
        ~Message();
        void swap(Message &, Message &);

        // 从给定 Folder 集合中添加/删除 本Message
        void save(Folder&);
        void remove(Folder&);

    private:
        string contents; // 实际消息文本
        set<Folder *> folders; // 包含 Message 的Folder

        // 将本消息添加到 m 的 folders 中
        void add_to_Folders(const Message&);

        // 从 folders 中的每个 Folder 中删除 Message
        void remove_from_Folders();
    };

    class Folder
    {
    public:
        void addMsg(const Message&);
        void removeMsg(const Message&);
    };




    Message::Message(const Message &m): contents(m.contents), folders(m.folders)
    {
        add_to_Folders(m); // 将本消息添加到指向 m 的 Folder 中
    }
    Message& Message::operator=(const Message &rhs)
    {
        remove_from_Folders();

        contents = rhs.contents;
        folders = rhs.folders;
        add_to_Folders(rhs);
        return *this;
    }

    void Message::swap(Message &lhs, Message &rhs)
    {
        using std::swap;
        // 将每个消息的指针从它原本所在的 Folder 中删除
        for (auto f: lhs.folders)
            f->removeMsg(lhs);
        for (auto f: rhs.folders)
            f->removeMsg(rhs);

        swap(lhs.contents, rhs.contents);
        swap(lhs.folders, rhs.folders);

        for (auto f: lhs.folders)
            f->addMsg(lhs);
        for (auto f: rhs.folders)
            f->addMsg(rhs);
    }
    Message::~Message()
    {
        remove_from_Folders();
    }
    void Message::save(Folder &f)
    {
        folders.insert(&f);  // 将给定 Folder 添加到我们的 Folder 列表中
        f.addMsg(*this);      // 将本 Message 添加到 f 的 Message 集合中
    }
    void Message::remove(Folder &f)
    {
        folders.erase(&f);    // 将给定 Folder 从我们的 Folder 列表中删除
        f.removeMsg(*this);    // 将本消息从 Folder 中删除
    }

    void Message::add_to_Folders(const Message &m)
    {
        for (const auto f: m.folders)
        {
            f -> addMsg(*this);
        }
    }
}


int main() {
    Message m1();
    cout << "hello" << endl;
    return 0;
}
