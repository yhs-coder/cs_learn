#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
using std::cout;
using std::endl;

#pragma comment(lib, "ws2_32.lib")

int main()
{
	// 初始化套接字库
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		cout << "WSAStartup err：" << GetLastError() << endl;
		return -1;
	}

	if (LOBYTE(wsa.wVersion) != 2 || HIBYTE(wsa.wVersion) != 2) {
		cout << "LOBYTE or HIBYTE error:" << GetLastError() << endl;
		WSACleanup();
		return -1;
	}

	cout << "this is UDP server..." << endl;

	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockSrv == INVALID_SOCKET) {
		cout << "socket error: " << GetLastError()
			<< endl;
		return -1;
	}
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(10001);

	if (SOCKET_ERROR == bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(addrSrv))) {
		cout << "bind error: " << GetLastError()
			<< endl;
			return -1;
	}

	// udp通信
	char recvBuf[256] = { 0 };
	char sendBuf[256] = { 0 };

	SOCKADDR_IN addrClt;	// 目标套接字地址信息
	int len = sizeof(addrClt);
	while (1) {
		// 接收数据
		recvfrom(sockSrv, recvBuf, sizeof(recvBuf), 0, (SOCKADDR*)&addrClt, &len);
		cout << "client IP: " << inet_ntoa(addrClt.sin_addr) << ", port: " << ntohs(addrClt.sin_port) << endl;
		cout << recvBuf << endl;

		sprintf(sendBuf, "UDP server received, ack: %s...",recvBuf);

		cout << "server sendBuf: " << sendBuf << endl;
		// 发送数据
		sendto(sockSrv, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrClt, len);

	}
	WIN32_FIND_DATA

	closesocket(sockSrv);
	WSACleanup();
	system("pause");
	return 0;
}

