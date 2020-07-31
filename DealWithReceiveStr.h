/*
 * DealWithReceiveStr.h
 *
 *  Created on: 2020年5月2日
 *      Author: root
 */

#ifndef SRC_DEALWITHRECEIVESTR_H_
#define SRC_DEALWITHRECEIVESTR_H_
#include <string>
#include <iostream>
#include <queue>
#include <mutex>

#include "tinyxml2.h"
#include "MessageLogical.h"
#include "CommonFlags.h"
#include "ConversationDealer.h"
using namespace std;
using namespace tinyxml2;

class DealWithReceiveStr {
public:
    bool DealWithString(string& str, ClientInfo* pInfo);
    DealWithReceiveStr();
	virtual ~DealWithReceiveStr();
	void PushMsgToQueue(MessageLogical& msg);
	void GetMsgFromQueue(MessageLogical& msg);
    static void DealWithMessage(DealWithReceiveStr* pDealer, ClientInfo* pCInfo);
protected:
	queue<MessageLogical> m_msgQueue;
    //static mutex some_mutex;
    mutex some_mutex;
	std::thread* m_pThread;
	vector<thread*> m_threadPtrVect;
};

#endif /* SRC_DEALWITHRECEIVESTR_H_ */
