#include "Server.h"

#define MYPORT 4399
#define BACKLOG 10
#define ARRAY_SIZE 256

typedef struct sockaddr_in SockAddr;


using namespace std;

XX_Server* XX_Server::m_Instance = NULL;

vector<UserInfo*> XX_Server::m_clientInfo;

const int RECEIVE_DATASIZE = 4096;

int	XX_Server::Start()
{
	int ret, sockfd, newSockFd;
	SockAddr mySerAddr, theirAddr;
	socklen_t sockLen = sizeof(SockAddr);
	socklen_t sin_size = sizeof(SockAddr);
	pid_t pid = 1;
	
	m_SockFd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		printf("Fail to create socket in server!\n");
		return -1;
	}
	
	mySerAddr.sin_family = AF_INET;
	mySerAddr.sin_port = htons(MYPORT);
	mySerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//bzero(&(mySerAddr.sin_zero), 8);
	memset(&(mySerAddr.sin_zero), 0, 8);
	
	ret = bind(m_SockFd, (const struct sockaddr*)&mySerAddr, sockLen);
	
	if(ret < 0)
	{
        printf("Fail to bind socket\n");
		return -1;
	}
	
	ret = listen(m_SockFd, BACKLOG);
	if(ret < 0)
	{
		printf("Fail to listen!\n");
		return -1;
	}
	else
	{
		printf("Server is listenning!\n");
	}

    UserInfo* pUserInfo = new UserInfo();
    ClientInfo& clientInfo = *(pUserInfo->m_pClientInfo);
	while(1)
	{
		if(pid != 0)
		{
			PRINT("going to accept\n");
			newSockFd = accept(m_SockFd, (struct sockaddr*)&theirAddr, &sin_size);
		}

		if(newSockFd < 0)
		{
			printf("error in accept\n");
			printf("pid is %d\n", pid);
			return -1;
		}

        //bool bDontLinger = false;
        //setsockopt(newSockFd, SOL_SOCKET, SO_DONTLINGER, (const char*)&bDontLinger, sizeof(bool));
		PRINT("going to create receving data thread for %s", clientInfo.m_ipAddr.c_str());
		clientInfo.m_socketFd = newSockFd;
		clientInfo.m_port = theirAddr.sin_port;
		char buf[256] = {0};
		inet_ntop(AF_INET, &theirAddr.sin_addr, buf, 255);
		clientInfo.m_ipAddr = string(buf);
		//m_socketFds.push(clientInfo);
		pthread_t threadForRecvId;
        clientInfo.m_pThreadId = new thread(XX_Server::Recv_data, (void*)&newSockFd);

        clientInfo.m_running = true;
        m_clientInfo.push_back(pUserInfo);

        printf("string(buf) is %s", buf);
        clientInfo.Print();


	}
}

void* XX_Server::Recv_data(void* params)
{
	int newSocketFd = (*(int*)params);
	char receive_data[RECEIVE_DATASIZE] = {0};
    UserInfo* pUsrInfo;
	while(1)
	{
		for(int i = 0; i<m_clientInfo.size(); i++)
		{
            if(m_clientInfo[i]->m_pClientInfo->m_socketFd == newSocketFd)
			{

                if(!m_clientInfo[i]->m_pClientInfo->m_running)
				{
					break;
				}
				else
				{
                    pUsrInfo = m_clientInfo[i];
				}
			}
		}
		memset(receive_data, 0, sizeof(receive_data));
		int ret = recv(newSocketFd, receive_data, RECEIVE_DATASIZE-1, 0);
		if(ret > 0)
		{
            Recv_dataHandler(receive_data, pUsrInfo);
		}
		else /*if(ret == 0)*/
		{
			break;
		}
	}
}

XX_Server::XX_Server()
{

}

void XX_Server::Recv_dataHandler(char* params, UserInfo* pInfo)
{
	static string receiveStr;
	receiveStr = string(params);
	PRINT("receive message %s\n", params);
    pInfo->m_pDealWithReceiveStr->DealWithString(receiveStr, pInfo->m_pClientInfo);
}
