/*
 * CommonFlags.h
 *
 *  Created on: Apr 16, 2017
 *      Author: root
 */

#ifndef SRC_COMMONFLAGS_H_
#define SRC_COMMONFLAGS_H_
#include <string>
#include <thread>
//#include "MessageRouter.h"
using namespace std;

#define PRINT printf

struct IInfo
{

};

typedef struct ClientInfo_t
{
	bool m_running;
	int m_socketFd;
	int m_port;
	string m_ipAddr;
	std::thread* m_pThreadId;
    IInfo* m_parent;
    ClientInfo_t():m_parent(NULL)
    {

    }
    ClientInfo_t(IInfo* pParent):m_parent(pParent)
	{
		m_running = false;
		m_port = 0;
		m_socketFd = 0;
		m_ipAddr = "";
		m_pThreadId = NULL;
	}
    ClientInfo_t& operator = (ClientInfo_t& right)
    {
        m_running = right.m_running;
        m_port = right.m_port;
        m_socketFd = right.m_socketFd;
        m_ipAddr = right.m_ipAddr;
        m_pThreadId = right.m_pThreadId;
        m_parent = right.m_parent;
        return *this;
    }
    IInfo* GetParent()
    {
        return m_parent;
    }

	void Print()
	{
	    PRINT("m_socketFd:%d,m_port:%d,m_ipAddr:%s,m_threadId:%p#", m_socketFd,m_port,m_ipAddr.c_str(),m_pThreadId);
	}
}ClientInfo;





#endif /* SRC_COMMONFLAGS_H_ */
