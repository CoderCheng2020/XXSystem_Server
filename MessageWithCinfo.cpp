#include "MessageWithCinfo.h"

MessageWIthCInfo::MessageWIthCInfo()
{
    //m_pString = new string();
}
MessageWIthCInfo::~MessageWIthCInfo()
{
    //delete m_pString;
}
MessageWIthCInfo::MessageWIthCInfo(MessageLogical& msg, ClientInfo& cInfo)
{
    m_msg = msg;
    m_cInfo = cInfo;
}

string& MessageWIthCInfo::ToString()
{
    const char* declaration ="<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";
    XMLDocument doc;
    doc.Parse(declaration);//会覆盖xml所有内容

        //添加申明可以使用如下两行
        //XMLDeclaration* declaration=doc.NewDeclaration();
        //doc.InsertFirstChild(declaration);

    XMLElement* root=doc.NewElement("Message");
    doc.InsertEndChild(root);

    /*XMLElement* userNode = doc.NewElement("Sequence");
    userNode->SetAttribute("Name",user.userName.c_str());
    userNode->SetAttribute("Password ",user.password.c_str());
    root->InsertEndChild(userNode);
    */
    char tempCharArray[10] = {0};
    XMLElement* sequenceElem = doc.NewElement("Sequence");
    memset(tempCharArray, 0, sizeof(tempCharArray));
    sprintf(tempCharArray, "%d", m_msg.Sequence);
    XMLText* sequenctText=doc.NewText(tempCharArray);
    sequenceElem->InsertEndChild(sequenctText);
    root->InsertEndChild(sequenceElem);

    XMLElement* sessionTypeElem = doc.NewElement("SessionType");
    memset(tempCharArray, 0, sizeof(tempCharArray));
    sprintf(tempCharArray, "%d", m_msg.sessionType);
    XMLText* sessionTypeText=doc.NewText(tempCharArray);
    sessionTypeElem->InsertEndChild(sessionTypeText);
    root->InsertEndChild(sessionTypeElem);

    XMLElement* sessionChildTypeElem = doc.NewElement("SessionChildType");
    memset(tempCharArray, 0, sizeof(tempCharArray));
    sprintf(tempCharArray, "%d", m_msg.sessionChildType);
    XMLText* sessionChildTypeText=doc.NewText(tempCharArray);
    sessionChildTypeElem->InsertEndChild(sessionChildTypeText);
    root->InsertEndChild(sessionChildTypeElem);

    XMLElement* messageDataElem = doc.NewElement("MessageData");
    XMLText* messageDataText=doc.NewText(m_msg.messageData.c_str());
    messageDataElem->InsertEndChild(messageDataText);
    root->InsertEndChild(messageDataElem);

    m_pString = doc.ToString();
    return m_pString;
   // return *m_pString;
}


