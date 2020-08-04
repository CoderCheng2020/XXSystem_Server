/*
 * TestClient.h
 *
 *  Created on: 2020年3月19日
 *      Author: root
 */

#ifndef SRC_TESTCLIENT_H_
#define SRC_TESTCLIENT_H_

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

#define PORT 80000

#define MAXDATASIZE 100 //数据缓冲区最大长度


class Test_Client {
public:
	Test_Client();
	virtual ~Test_Client();
	bool ConnectServer(const string& serverIP);
};

#endif /* SRC_TESTCLIENT_H_ */
