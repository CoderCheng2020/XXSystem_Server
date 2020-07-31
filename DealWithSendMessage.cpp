#include "DealWithSendMessage.h"


bool DealWithSendMessage::m_bRunning = true;

DealWithSendMessage::DealWithSendMessage()
{
    m_pSendMsgThread = new thread(SendMessage, this);
}

 DealWithSendMessage::~DealWithSendMessage()
 {
    m_bRunning = false;
    delete m_pSendMsgThread;
 }

void DealWithSendMessage::PushMsgToQueue(MessageWIthCInfo msg)
{
    std::lock_guard<std::mutex> guard(m_someMutex);
    m_msgQueue.push(msg);
}

bool DealWithSendMessage::GetMsgFromQueue(MessageWIthCInfo& msg)
{
    std::lock_guard<std::mutex> guard(m_someMutex);
    if(m_msgQueue.empty())
    {
        return false;
    }   
    msg = m_msgQueue.front();
    m_msgQueue.pop();
    return true;
}

void DealWithSendMessage::SendMessage(DealWithSendMessage* pDealer)
{
    while(1)
    {
        if(!m_bRunning)
        {
            break;
        }
        MessageWIthCInfo msg;
        bool IsHaveMessage = pDealer->GetMsgFromQueue(msg);


        if(IsHaveMessage)
        {
            string messageStr = msg.ToString();
            PRINT("messageStr is %s\n", messageStr.c_str());
            int ret;
            ret = send(msg.m_cInfo.m_socketFd, messageStr.c_str(), messageStr.length(), 0);

            if(ret > 0)
            {
                PRINT("write %d bytes to %s", ret, msg.m_cInfo.m_ipAddr.c_str());
            }
        }

    }
}
