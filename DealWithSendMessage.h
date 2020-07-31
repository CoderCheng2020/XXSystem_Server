#ifndef DEALWITHSENDMESSAGE_H
#define DEALWITHSENDMESSAGE_H
#include <mutex>
#include <queue>
#include <string>
#include "MessageWithCinfo.h"
#include <sys/socket.h>   //connect,send,recv,setsockopt等
#include <sys/types.h>

#include <netinet/in.h>     // sockaddr_in, "man 7 ip" ,htons
#include <poll.h>             //poll,pollfd
#include <arpa/inet.h>   //inet_addr,inet_aton
#include <unistd.h>        //read,write
#include <netdb.h>         //gethostbyname

#include <error.h>         //perror
#include <stdio.h>
#include <errno.h>         //errno

#include <string.h>          // memset
#include <string>
#include <iostream>

using namespace std;

class DealWithSendMessage
{
public:
    DealWithSendMessage();
    static void SendMessage(DealWithSendMessage* pDealer);
    void PushMsgToQueue(MessageWIthCInfo msg);
    bool GetMsgFromQueue(MessageWIthCInfo& msg);
    ~DealWithSendMessage();
protected:
    mutex m_someMutex;
    queue<MessageWIthCInfo> m_msgQueue;
    static bool m_bRunning;
    thread* m_pSendMsgThread;
};

#endif // DEALWITHSENDMESSAGE_H
