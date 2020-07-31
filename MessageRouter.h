#ifndef MESSAGEROUTER_H
#define MESSAGEROUTER_H
#include <map>
#include "CommonFlags.h"
#include "DealWithReceiveStr.h"
#include "DealWithSendMessage.h"
#include <thread>

using namespace std;

class UserInfo: public IInfo
{
public:
    UserInfo()
    {
        m_pClientInfo = new ClientInfo(this);
        m_pDealWithSendMsg = new DealWithSendMessage();
        m_pDealWithReceiveStr = new DealWithReceiveStr();
    }
    ~UserInfo()
    {
        delete m_pClientInfo;
        delete m_pDealWithSendMsg;
        delete m_pDealWithReceiveStr;
    }
    MessageWIthCInfo& CombineMessage(MessageLogical& msg);
    DealWithSendMessage* GetDealWithSendMessagePtr(){return m_pDealWithSendMsg;}
    DealWithReceiveStr*      GetDealWithReceiveStrPtr(){return m_pDealWithReceiveStr;}
public:
    MessageWIthCInfo m_msgWithClnfo;
    ClientInfo* m_pClientInfo;
    DealWithSendMessage* m_pDealWithSendMsg;
    DealWithReceiveStr* m_pDealWithReceiveStr;
};

enum MessageType
{
    MSG_TEXT=0,//text message
    MSG_TEXT_GROUP,//text message for group
    MSG_AUDIO,//audio message
    MSG_AUDIO_GROUP,
    MSG_VEDIO,
    MSG_VEDIO_GROUP
};

struct DialogNode
{
    string m_hostId;
    string m_friendId;
    string m_content;
    MessageType m_messageType;
    MessageLogical m_message;
};


class MessageRouter
{
public:
    static MessageRouter* GetInstance()
    {
        if(m_instance == NULL)
        {
            m_instance = new MessageRouter();
        }
        return m_instance;
    }
    ~MessageRouter()
    {
        if(m_instance != NULL)
        {
            delete m_instance;
        }
        m_bExitInquireThread = true;
        sleep(1000);
        delete m_pInquireThread;
    }
    static void DealWithDialogQueueMsg(MessageRouter* pRouter);
    void PushDialogNodeToQueue(DialogNode& node);
    bool GetNodeFromQueue(DialogNode& node);
    void AddUser(const string& userId, UserInfo* pUsrInfo)
    {
        m_routerMap[userId] = pUsrInfo;
    };
    void SendMsgToFriend(string& friendId, string& content);
protected:
    mutex m_mutex;
    queue<DialogNode> m_DialogNodeQueue;
    MessageRouter();
    map<string, UserInfo*> m_routerMap;
    static MessageRouter* m_instance;
    thread* m_pInquireThread;
    static bool m_bExitInquireThread;
};


#endif // MESSAGEROUTER_H
