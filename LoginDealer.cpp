/*
 * LoginDealer.cpp
 *
 *  Created on: 2020年5月8日
 *      Author: root
 */

#include "LoginDealer.h"

LoginDealer::LoginDealer() {
	// TODO Auto-generated constructor stub

}

LoginDealer::~LoginDealer() {
	// TODO Auto-generated destructor stub

}

void LoginDealer::DealWithLoginMessage(MessageLogical& msg, ClientInfo* pInfo)
{
	if(msg.sessionChildType == CTS_LOGIN)//client to server login
	{
		vector<string> msgDataVect;
		CommonFunctions::GetInstance()->SplitString(msg.messageData, ",",msgDataVect);
		if(msgDataVect.size() == 2)
		{
            string userId = msgDataVect[0];
			string pwdStr = msgDataVect[1];

			string executeResultStr = "";
            string sqlStr = "select * from Users where TelephoneId="+userId;
			AccessDB::GetInstance()->executeSQL(sqlStr, executeResultStr);

			cout<<executeResultStr<<endl;

			vector<string> resultVect;
			CommonFunctions::GetInstance()->SplitString(executeResultStr, "#",resultVect);

            map<string, string> userInfoMap;
			for(int i=0; i<resultVect.size(); i++)
			{
                vector<string> fieldNameAndValueVect;
				CommonFunctions::GetInstance()->SplitString(resultVect[i], ",", fieldNameAndValueVect);
				if(fieldNameAndValueVect.size() == 2)
				{
					userInfoMap[fieldNameAndValueVect[0]] = fieldNameAndValueVect[1];
				}
			}
            try
            {
                MessageWIthCInfo message;
                if(pwdStr != userInfoMap["Password"])
                {
                    message.m_msg.Sequence = msg.Sequence+1;
                    message.m_msg.sessionType = LOGIN;
                    message.m_msg.sessionChildType = STC_LOGIN_REPLY;
                    message.m_msg.messageData = "Fail#Wrong Password!";
                }
                else
                {

                    //auto it = userInfoMap.begin();
                    MessageRouter::GetInstance()->AddUser(userInfoMap["TelephoneId"], (UserInfo*)pInfo->GetParent());//1002, UserInfo
                    message.m_msg.Sequence = msg.Sequence+1;
                    message.m_msg.sessionType = LOGIN;
                    message.m_msg.sessionChildType = STC_LOGIN_REPLY;
                    message.m_msg.messageData = "Success";
                }
                message.m_cInfo = *pInfo;
                UserInfo* pUserInfo = static_cast<UserInfo*>(message.m_cInfo.GetParent());
                if(pUserInfo != NULL)
                {
                    pUserInfo->m_pDealWithSendMsg->PushMsgToQueue(message);
                }
            }
            catch(exception* e)
            {
                PRINT("e is %s\n", e->what());
            }
        }
    }
    else if(msg.sessionChildType == CTS_LOGIN_REQUIRE_FRIEND_LIST)
    {
        string executeResultStr;
        string sqlStr = "select Users.*, User_Friends.GroupStr, User_Friends.FriendId from Users, User_Friends where Users.TelephoneId = User_Friends.FriendId && User_Friends.XXId = "+msg.messageData;
        AccessDB::GetInstance()->executeSQL(sqlStr, executeResultStr);


        vector<string> singleRowInfoVect;//eg. executeResultStr::GroupStr,MyFriends#FriendId,1001#%GroupStr,MyFriends#FriendId,1002#%
        CommonFunctions::GetInstance()->SplitString(executeResultStr, "%",singleRowInfoVect);
                                              //eg. resultVect::GroupStr,MyFriends#FriendId,1001#
        vector<map<string, string> > friendInfoVect;
        map<string, string> friendInfoMap;
        for(int i=0; i<singleRowInfoVect.size(); i++)
        {
            friendInfoMap.clear();
            vector<string> singleFieldInfoVect; //eg. resultVect::GroupStr,MyFriend
            CommonFunctions::GetInstance()->SplitString(singleRowInfoVect[i], "#",singleFieldInfoVect);

            for(int j=0; j<singleFieldInfoVect.size(); j++)
            {
                vector<string> singleInfoVect;
                CommonFunctions::GetInstance()->SplitString(singleFieldInfoVect[j], ",",singleInfoVect);

                if(singleInfoVect.size() == 2)
                {
                    friendInfoMap[singleInfoVect[0]] = singleInfoVect[1];
                }
            }
            friendInfoVect.push_back(friendInfoMap);

        }

        string vectorStr;
        ParseVectorIntoString(friendInfoVect, vectorStr);

         MessageWIthCInfo message;

         message.m_msg.Sequence = msg.Sequence+1;
         message.m_msg.sessionType = LOGIN;
         message.m_msg.sessionChildType = STC_LOGIN_REQUIRE_FRIEND_LIST_REPLY;
         message.m_msg.messageData = vectorStr;

         message.m_cInfo = *pInfo;
         ((UserInfo*)pInfo->GetParent())->m_pDealWithSendMsg->PushMsgToQueue(message);
    }
}

void LoginDealer::ParseVectorIntoString(vector<map<string, string>>& vect, string& resultStr)
{
    //const char* declaration ="<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";
    XMLDocument doc;
   // doc.Parse(declaration);//会覆盖xml所有内容

        //添加申明可以使用如下两行
        //XMLDeclaration* declaration=doc.NewDeclaration();
        //doc.InsertFirstChild(declaration);

    XMLElement* root=doc.NewElement("FriendInfo");
    doc.InsertEndChild(root);

    char tempCharArray[10] = {0};
    XMLElement* rowNumberElem = doc.NewElement("RowNumber");
    memset(tempCharArray, 0, sizeof(tempCharArray));
    sprintf(tempCharArray, "%d", vect.size());
    XMLText* rowNumberText=doc.NewText(tempCharArray);
    rowNumberElem->InsertEndChild(rowNumberText);
    root->InsertEndChild(rowNumberElem);

    for(int i=0; i<vect.size(); i++)
    {
        char tempCharArray[10] = {0};

        memset(tempCharArray, 0, sizeof(tempCharArray));
        sprintf(tempCharArray, "Row%d", i);
          XMLElement* rowElem = doc.NewElement(tempCharArray);
        /*XMLText* rowText=doc.NewText(tempCharArray);
        rowElem->InsertEndChild(rowText);*/
        root->InsertEndChild(rowElem);

        map<string,string>& friendInfoMap = vect[i];
        map<string,string>::iterator it = friendInfoMap.begin();
        for(;it != friendInfoMap.end(); it++)
        {

             XMLElement* infoElem = doc.NewElement(it->first.c_str());
             XMLText* rowText=doc.NewText(it->second.c_str());
             infoElem->InsertEndChild(rowText);
             rowElem->InsertEndChild(infoElem);
        }
    }
    resultStr = doc.ToString();
}
