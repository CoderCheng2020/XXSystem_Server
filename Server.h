/*
 * Server.h
 *
 *  Created on: Apr 15, 2017
 *      Author: root
 */

#ifndef SRC_SERVER_H_
#define SRC_SERVER_H_

#include<cstdlib>
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include <netdb.h>
#include<sys/wait.h>
#include<netinet/in.h>
#include<pthread.h>

#include<stdio.h>
#include<string.h>
#include<vector>
#include<string>
#include<arpa/inet.h>
#include<unistd.h>
#include <thread>

#include "CommonFlags.h"
#include "DealWithReceiveStr.h"
#include "CommonFlags.h"
#include "MessageRouter.h"
using namespace std;

class XX_Server
{
public:
	XX_Server();
	int	Start();
	static XX_Server* GetInstance()
	{
		if(m_Instance == NULL)
		{
			m_Instance = new XX_Server();
		}
		return m_Instance;
	}
	static void* Recv_data(void* params);
    static void Recv_dataHandler(char* params, UserInfo* pInfo);

	~XX_Server()
	{
		if(m_Instance != NULL)
		{
			delete m_Instance;
		}
		for(int i = 0; i<m_clientInfo.size(); i++)
            m_clientInfo[i]->m_pClientInfo->m_running = false;
        sleep(1000);
        for(int i=0; i<m_clientInfo.size(); i++)
        {
            delete m_clientInfo[i];
        }
		close(m_SockFd);
	}
private:
	int m_SockFd;
    static vector<UserInfo*> m_clientInfo;
	static XX_Server* m_Instance;
	std::thread* m_pReceiveThread;
};
//XX_Server* XX_Server::m_Instance = NULL;
#endif /* SRC_SERVER_H_ */
