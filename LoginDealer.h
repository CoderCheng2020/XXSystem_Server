/*
 * LoginDealer.h
 *
 *  Created on: 2020年5月8日
 *      Author: root
 */

#ifndef SRC_LOGINDEALER_H_
#define SRC_LOGINDEALER_H_
#include "MessageLogical.h"
#include "CommonFunctions.h"
#include "AccessDB.h"
#include "CommonFlags.h"
#include "MessageWithCinfo.h"
#include "DealWithSendMessage.h"
#include "MessageRouter.h"
#include <vector>
#include <map>

using namespace std;


class LoginDealer {
public:
	LoginDealer();
    void ParseVectorIntoString(vector<map<string, string>>& vect, string& resultStr);
    void DealWithLoginMessage(MessageLogical& msg, ClientInfo* pInfo);
	virtual ~LoginDealer();
};

#endif /* SRC_LOGINDEALER_H_ */
