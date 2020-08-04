#include "soapcalcService.h"
#include "calc.nsmap"
#include <iostream>
using namespace std;


int calcService:: SendAndReceiveMessage(char *sendMesssage, char **recevieMessage)
{
        cout<< "receive message:"<<sendMesssage<<endl;
        *recevieMessage = (char*)soap_malloc(this, 1024);
        sprintf(*recevieMessage, "Hello, world!");
        return SOAP_OK;
}




