//#include "stdafx.h"
#include <WinSock2.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

const int MAX_BUF_LEN = 255;

int _tmain(int argc, _TCHAR* argv[])
{
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	double time;
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	// 启动socket api
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return -1;
	}

	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return -1;
	}

	// 创建socket
	SOCKET connect_socket;
	connect_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == connect_socket)
	{
		err = WSAGetLastError();
		printf("/socket /  error! error code is %d/n", err);
		return -1;
	}

	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(3779);
	sin.sin_addr.s_addr = INADDR_BROADCAST;

	bool bOpt = true;
	//设置该套接字为广播类型
	setsockopt(connect_socket, SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));

	int nAddrLen = sizeof(SOCKADDR);

	SOCKADDR_IN tem;
	int temlen = sizeof(SOCKADDR);

	char buff[MAX_BUF_LEN] = "111";
	char recebuf[MAX_BUF_LEN];
	int nLoop = 0;
	while (1)
	{
		system("pause");
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBeginTime);
		for (int a = 0; a < 1000; a++) {
			nLoop++;
			sprintf(buff, "%8d", nLoop);

			// 发送数据
			
			int nSendSize = sendto(connect_socket, buff, strlen(buff), 0, (SOCKADDR*)&sin, nAddrLen);
			//sendto(connect_socket, buff, strlen(buff), 0, (SOCKADDR*)&sin, nAddrLen);
			/*if (SOCKET_ERROR == nSendSize)
			{
				err = WSAGetLastError();
				printf("/sendto /  error!, error code is %d/n", err);
				return -1;
			}*/
			//printf("Send: %s\n", buff);
			//recvfrom(connect_socket, recebuf, MAX_BUF_LEN, 0, (SOCKADDR*)&tem, &temlen);
			//recvfrom(connect_socket, recebuf, MAX_BUF_LEN, 0, (SOCKADDR*)&sin, &nAddrLen);
			Sleep(1);

		}
		QueryPerformanceCounter(&nEndTime);
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
		printf("%f us \n", time * 1000000);
		//Sleep(1);
	}

	return 0;
}