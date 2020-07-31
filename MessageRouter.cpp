#include "MessageRouter.h"

MessageRouter* MessageRouter::m_instance = NULL;
bool MessageRouter::m_bExitInquireThread = false;

 MessageWIthCInfo& UserInfo::CombineMessage(MessageLogical& msg)
 {
     m_msgWithClnfo.m_msg = msg;
     m_msgWithClnfo.m_cInfo = *m_pClientInfo;
     return m_msgWithClnfo;
 }

MessageRouter::MessageRouter()
{
    m_pInquireThread = new thread(DealWithDialogQueueMsg, this);
}
void MessageRouter::PushDialogNodeToQueue(DialogNode& node)
{
    lock_guard<mutex> lk(m_mutex);
    m_DialogNodeQueue.push(node);
}
bool MessageRouter::GetNodeFromQueue(DialogNode& node)
{
    lock_guard<mutex> lk(m_mutex);
    if(m_DialogNodeQueue.empty())
    {
        return false;
    }

    node = m_DialogNodeQueue.front();
    m_DialogNodeQueue.pop();
    return true;
}

void MessageRouter::DealWithDialogQueueMsg(MessageRouter* pRouter)
{
    while(1)
    {
        if(m_bExitInquireThread)
        {
            break;
        }
        DialogNode msg;
        bool ret = pRouter->GetNodeFromQueue(msg);
        if(ret)
        {
            for(auto it = pRouter->m_routerMap.begin(); it != pRouter->m_routerMap.end(); ++it)
            {
                if(msg.m_friendId == it->first)
                {
                    UserInfo* pUsrInfo = it->second;
                    pUsrInfo->GetDealWithSendMessagePtr()->PushMsgToQueue(pUsrInfo->CombineMessage(msg.m_message));
                    break;
                }
            }
        }
    }
}
