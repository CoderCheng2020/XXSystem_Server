#include "ConversationDealer.h"
#include "tinyxml2.h"
#include "MessageRouter.h"

using namespace tinyxml2;

ConversationDealer::ConversationDealer()
{

}

void ConversationDealer::DealWithConversationMessage(MessageLogical& msg, ClientInfo* pInfo)
{
    DialogNode node;
    XMLDocument doc;
    doc.Parse(msg.messageData.c_str());

    const XMLElement* converElem = doc.FirstChildElement();
    if(converElem != NULL)
    {
        const XMLElement* hostIdElem = converElem->FirstChildElement();
        if(hostIdElem != NULL)
        {
            const XMLNode* hostIdNode = hostIdElem->FirstChild();
            if(hostIdNode != NULL)
            {
                //m_hostId = hostIdNode->Value();
                node.m_hostId = hostIdNode->Value();
            }
        }
         const XMLElement* friendIdElem = hostIdElem->NextSiblingElement();
         if(friendIdElem != NULL)
         {
             const XMLNode* friendIdNode = friendIdElem->FirstChild();
             if(friendIdNode != NULL)
             {
                 //m_friendId = friendIdNode->Value();
                 node.m_friendId = friendIdNode->Value();
             }
         }

         const XMLElement* contentElem = friendIdElem->NextSiblingElement();
         if(contentElem != NULL)
         {
             const XMLNode* contentNode = contentElem->FirstChild();
             if(contentNode != NULL)
             {
                 //m_content = contentNode->Value();
                 node.m_content = contentNode->Value();
             }
         }
    }
    else
    {
        return;
    }
    node.m_message = msg;
    node.m_messageType = MSG_TEXT;//Just default to MSG_TEXT temperary
    MessageRouter::GetInstance()->PushDialogNodeToQueue(node);
}
