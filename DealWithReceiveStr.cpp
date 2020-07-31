/*
 * DealWithReceiveStr.cpp
 *
 *  Created on: 2020年5月2日
 *      Author: root
 */

#include "DealWithReceiveStr.h"
#include "LoginDealer.h"

//mutex DealWithReceiveStr::some_mutex;

DealWithReceiveStr::DealWithReceiveStr() {
	// TODO Auto-generated constructor stub

}

DealWithReceiveStr::~DealWithReceiveStr() {
	// TODO Auto-generated destructor stub
	for(int i=0; i<m_threadPtrVect.size(); i++)
	{
		delete m_threadPtrVect[i];
	}

}


bool DealWithReceiveStr::DealWithString(string& str, ClientInfo* pInfo)
{
	static MessageLogical message;
    XMLDocument doc;
	doc.Parse(str.c_str());

    const XMLElement* MessageElem = doc.FirstChildElement();
	if(MessageElem != NULL)
	{
        const XMLElement* sequenceElem = MessageElem->FirstChildElement();
		if(sequenceElem != NULL)
		{
            const XMLNode* seqChildNode = sequenceElem->FirstChild();
			if(seqChildNode != NULL)
			{
				PRINT("seqChildElem->Value() is %s", seqChildNode->Value());
				message.Sequence = stoi(seqChildNode->Value());
			}
		}
        const XMLElement* sessionTypeElem = sequenceElem->NextSiblingElement();
		if(sessionTypeElem != NULL)
		{
            const XMLNode* sessionTypeNode = sessionTypeElem->FirstChild();
			if(sessionTypeNode != NULL)
			{
				message.sessionType = (Session_Type)stoi(sessionTypeNode->Value());
			}
		}

        const XMLElement* sessionChildTypeElem = sessionTypeElem->NextSiblingElement();
		if(sessionChildTypeElem != NULL)
		{
            const XMLNode* sessionchildchildTypeNode = sessionChildTypeElem->FirstChild();
			if(sessionchildchildTypeNode != NULL)
			{
				message.sessionChildType = (Session_Child_Type)stoi(sessionchildchildTypeNode->Value());
			}
		}

        const XMLElement* messageDataElem = sessionChildTypeElem->NextSiblingElement();
		if(messageDataElem != NULL)
		{
            const XMLNode* messageDataChildNode = messageDataElem->FirstChild();
            if(messageDataChildNode != NULL)
			{
				message.messageData = messageDataChildNode->Value();
			}
		}
	}

	PushMsgToQueue(message);

    m_pThread = new thread(DealWithMessage, this, pInfo);
    //m_threadPtrVect.push_back(m_pThread);
    //DealWithMessage(this, pInfo);
}

void DealWithReceiveStr::PushMsgToQueue(MessageLogical& msg)
{
    //std::lock_guard<std::mutex> guard(some_mutex);
    some_mutex.lock();
    m_msgQueue.push(msg);
    some_mutex.unlock();
}

void DealWithReceiveStr::GetMsgFromQueue(MessageLogical& msg)
{
    //std::lock_guard<std::mutex> guard(some_mutex);
    some_mutex.lock();
	msg = m_msgQueue.front();
	m_msgQueue.pop();
    some_mutex.unlock();
}

void DealWithReceiveStr::DealWithMessage(DealWithReceiveStr* pDealer, ClientInfo* pCInfo)
{
    try
    {
        MessageLogical msg;
        pDealer->GetMsgFromQueue(msg);
        switch(msg.sessionType)
        {
        case LOGIN://login operation
            {
                LoginDealer loginDealer;
                loginDealer.DealWithLoginMessage(msg, pCInfo);
                break;
            }
         case CONVERSATION:
            {
                ConversationDealer converDealer;
                converDealer.DealWithConversationMessage(msg, pCInfo);
            }
            break;
        }
    }
    catch(exception* e)
    {
        PRINT("e is %s at line:%d in %s\n", e->what(), __LINE__, __FUNCTION__);
    }
}
