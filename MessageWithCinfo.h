#ifndef MESSAGEWITHCINFO_H
#define MESSAGEWITHCINFO_H
#include "MessageLogical.h"
#include "CommonFlags.h"
#include "tinyxml2.h"
#include <stdlib.h>

using namespace tinyxml2;


class MessageWIthCInfo
{
public:
    MessageWIthCInfo();
    ~MessageWIthCInfo();
    MessageWIthCInfo(MessageLogical& msg, ClientInfo& cInfo);
    string& ToString();
    MessageLogical m_msg;
    ClientInfo m_cInfo;
    string m_pString;
};

#endif // MESSAGEWITHCINFO_H
