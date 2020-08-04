/*
 * TestClient.cpp
 *
 *  Created on: 2020年3月19日
 *      Author: root
 */

#include "TestClient.h"

int main()
{
	Test_Client client;
	const string serverIP("127.0.0.1");
	client.ConnectServer(serverIP);

}

Test_Client::Test_Client() {
	// TODO Auto-generated constructor stub

}

Test_Client::~Test_Client() {
	// TODO Auto-generated destructor stub
}

bool Test_Client::ConnectServer(const string& serverIP)
{
	int sockfd, num;
	//数据缓冲区
	char buf[MAXDATASIZE] = {0};
	struct hostent *he;
	//服务器IPv4地址信息
	struct sockaddr_in server;


	//通过gethostbyname()得到服务端的主机信息
	if((he = gethostbyname(serverIP.c_str())) == NULL)
	{
		printf("gethostbyname() error\n");
		return false;
	}

	//使用socket()创建套接字
	if((sockfd= socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("socket() error\n");
		return false;
	}

	//初始化server地址信息
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr = *((struct in_addr *)he->h_addr);

	//使用connect()函数来配置套接字，建立一个与TCP服务器的连接
	if(connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		printf("connect() error\n");
		return false;
	}
	memcpy(buf, "Hello, world!", sizeof("Hello, world!"));
	num = send(sockfd, buf, strlen(buf), 0);

	//使用recv()函数接收服务器发送的信息
	if((num = recv(sockfd, buf, MAXDATASIZE, 0)) == -1)
	{
		printf("recv() error\n");
		return false;
	}

	buf[num - 1] = '\0';
	printf("server message: %s\n", buf);
	//关闭连接
	close(sockfd);
}


