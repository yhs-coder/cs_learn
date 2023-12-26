#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
using namespace std;
/*
	客户端做的事情：
	1. 等待服务端开启服务并建立连接
	2. 发送消息：等待用户往控制台输入消息，然后发送给服务端 （客户名 + 消息）
	3. 客户端等待服务端的消息：即接收其它客户端的消息
	4. 客户端主动退出连接，即下线
*/

#pragma comment(lib, "ws2_32.lib")
#define MAX_NAME_SIZE 128
#define MAX_BUF_SIZE 256

char szName[MAX_NAME_SIZE] = "[default]"; // 客户端名称 
char szMsg[MAX_BUF_SIZE] = { 0 };	// 收发数据的缓冲区


DWORD CALLBACK SendMsg(LPVOID lpParam)
{
	SOCKET conSock = *((SOCKET*)lpParam);
	char szNameMsg[MAX_BUF_SIZE + MAX_NAME_SIZE] = { 0 };	// 存储客户端名和消息
	int len = 0;
	while (1) {
		memset(szMsg, 0, MAX_BUF_SIZE);		// 清空数据缓冲区
		fgets(szMsg, MAX_BUF_SIZE, stdin);
		// cout << "strlen(szMsg) = " << strlen(szMsg) << endl;  // 发送字符串时，\n回车键也是其中一个字符
		if (!strcmp(szMsg, "Q\n") || !strcmp(szMsg, "q\n")) {
			cout << "Client actively disconnects..." << endl;
			closesocket(conSock);
			exit(0);
		}
		// 拼接消息
		sprintf(szNameMsg, "[%s]: %s", szName, szMsg);
		send(conSock, szNameMsg, strlen(szNameMsg), 0);
	}
}

DWORD CALLBACK RecvMsg(LPVOID lpParam)
{
	SOCKET conSock = *((SOCKET*)lpParam);
	char szNameMsg[MAX_BUF_SIZE + MAX_NAME_SIZE] = { 0 };	// 存储客户端名和消息
	int len = 0;
	while (1) {
		len = recv(conSock, szNameMsg, sizeof(szNameMsg), 0);
		if (len != -1) {		
			szNameMsg[len] = 0;
			fputs(szNameMsg, stdout);
			//cout << szNameMsg << endl;
		} else {
			cout << "server disconnect..." << endl;
			return 2;
		}
	}
	return 0;
}


int main(int argc, char* argv[])
{
	// 从控制台输入客户端名
	if (argc != 2) {
		cout << "Two parameters must be entered" << endl;
		cout << "for example: ./xxx.exe client_name" << endl;
		system("pause");
		return -1;
	}
	cout << "-----------------" << endl;
	sprintf(szName, "%s", argv[1]);
	cout << szName << endl;
	cout << "-----------------" << endl;

	WSADATA wsaData{};
	int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != 0) {
		cout << "WSAStartup  error : " << GetLastError() << endl;
		return -1;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		cout << "LOBYTE || HIBYTE error :" << GetLastError() << endl;
		WSACleanup();
		return -1;
	}

	SOCKET cltSock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == cltSock) {
		cout << "socket error：" << GetLastError() << endl;
		return -1;
	}

	SOCKADDR_IN srvAddr;
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	srvAddr.sin_port = htons(66666);
	if (SOCKET_ERROR == connect(cltSock, (SOCKADDR*)&srvAddr, sizeof(srvAddr))){
		cout << "connect error: "<< GetLastError() << endl;
			return -1;
	}
	HANDLE sendThread, recvThread;
	DWORD tId = 0;
	sendThread = CreateThread(NULL, 0, SendMsg, &cltSock, 0, &tId);
	recvThread = CreateThread(NULL, 0, RecvMsg, &cltSock, 0, &tId);

	WaitForSingleObject(sendThread, INFINITE);
	WaitForSingleObject(recvThread, INFINITE);
	closesocket(cltSock);
	WSACleanup();
	return 0;
}

