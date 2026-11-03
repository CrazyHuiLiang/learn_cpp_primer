#ifndef Folder_H
#define Folder_H

#include <cstddef>
#include <set>
class Message;

class Folder
{
    friend class Message;
    friend void swap(Message&, Message&);
public:
    // 书中未提供，仅为演示观察：本 Folder 持有多少条 Message
    std::size_t message_count() const { return messages.size(); }

private:
    void addMsg(Message*);
    void remMsg(Message*);
    std::set<Message*> messages;
};
#endif
