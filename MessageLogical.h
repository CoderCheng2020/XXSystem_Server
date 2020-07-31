/*
 * MessageLogical.h
 *
 *  Created on: Apr 16, 2017
 *      Author: root
 */

#ifndef SRC_MESSAGELOGICAL_H_
#define SRC_MESSAGELOGICAL_H_

#include <string>

using namespace std;

typedef enum
{
    LOGIN=1,
    SEARCH,
    CONVERSATION
}Session_Type;

typedef enum
{
/*************************************************/
/*for login module*/
	CTS_LOGIN = 1,
	STC_LOGIN_REPLY = 2,
	CTS_LOGIN_REQUIRE_FRIEND_LIST = 3,
	STC_LOGIN_REQUIRE_FRIEND_LIST_REPLY = 4,
/*************************************************/

/*************************************************/
/*for search module*/
	CTS_SEARCH_USER_ACCOUNT = 1,
	STC_SEARCH_USER_ACCOUNT_REPLY = 2,
/*************************************************/

    /*************************************************/
    /*for conversation*/
        CTS_START_CONVERSATION = 1,
        STC_START_CONVERSATION = 2,
    /*************************************************/
}Session_Child_Type;

#define MESSAGESTR "Message"

class MessageLogical {
public:
	int Sequence;
	Session_Type sessionType;
	Session_Child_Type sessionChildType;
	string messageData;
	MessageLogical();
    string& ToString();
	virtual ~MessageLogical();
};

#endif /* SRC_MESSAGELOGICAL_H_ */
