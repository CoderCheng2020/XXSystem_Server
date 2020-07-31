#ifndef CONVERSATIONDEALER_H
#define CONVERSATIONDEALER_H
#include "MessageLogical.h"
#include "CommonFlags.h"


class ConversationDealer
{
public:
    ConversationDealer();
    void DealWithConversationMessage(MessageLogical& msg, ClientInfo* pInfo);
protected:
    string m_hostId;
    string m_friendId;
    string m_content;
};

#endif // CONVERSATIONDEALER_H
