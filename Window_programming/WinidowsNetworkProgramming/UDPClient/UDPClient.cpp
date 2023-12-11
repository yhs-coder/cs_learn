#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
using std::cout;
using std::endl;

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		cout << "WSAStartup err：" << GetLastError() << endl;
		return -1;
	}

	if (LOBYTE(wsa.wVersion) != 2 || HIBYTE(wsa.wVersion) != 2) {
		cout << "LOBYTE or BIBYTE error:" << GetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "this is UDP client..." << endl;


	SOCKET sockClt = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockClt == INVALID_SOCKET) {
		cout << "socket error: " << GetLastError()
			<< endl;
		return -1;
	}

	// 目标套接字地址信息
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(10001);
	int len = sizeof(addrSrv);
	// udp通信
	char recvBuf[256] = { 0 };
	char sendBuf[256] = "hello world!";

	// 发送数据
	sendto(sockClt, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrSrv, len);

	// 接收数据
	recvfrom(sockClt, recvBuf, sizeof(recvBuf), 0, (SOCKADDR*)&addrSrv, &len);
	cout << recvBuf << endl;


	closesocket(sockClt);
	WSACleanup();
	system("pause");
	return 0;
}


