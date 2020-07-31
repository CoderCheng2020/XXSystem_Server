/*
 * Main.cpp
 *
 *  Created on: Apr 15, 2017
 *      Author: root
 */
#include "Server.h"

int main()
{
	XX_Server* pServer = XX_Server::GetInstance();
	pServer->Start();
}



