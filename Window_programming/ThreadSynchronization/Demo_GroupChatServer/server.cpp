#include <windows.h>
#include <iostream>
using namespace std;

/*
	群聊服务器：
		- 每当一个连接的客户端发来消息，就将消息发送给所有已建立连接的客户端
		- 每当客户端下线时，便去找数组中下线的客户端位置，并将后面的位置前移
		- 对临界资源或代码段加锁保护
*/

#pragma comment(lib, "ws2_32.lib")
#define MAX_SIZE 5
#define MAX_BUF_SIZE 256

HANDLE g_hMutex = 0;
SOCKET cltSocks[MAX_SIZE] = {0};	// 所有连接客户端的socket数组
int cltCount = 0;				// 连接客户端的数量

void SendMsg(char* msg, size_t len)
{
	WaitForSingleObject(g_hMutex, INFINITE);
	// 将消息发送给所有连接的客户端
	for (int i = 0; i < cltCount; i++) {
		send(cltSocks[i], msg, len, 0);
	}
	ReleaseMutex(g_hMutex);
}

DWORD CALLBACK HandleClt(LPVOID lpParam)
{
	SOCKET sockClt = *((SOCKET*)lpParam);
	char msgBuf[MAX_BUF_SIZE];
	while (1) {
		memset(msgBuf, 0, sizeof(msgBuf));	// 每接收一次，就清空缓冲区的内容
		int len = recv(sockClt, msgBuf, sizeof(msgBuf), 0);
		if (len != -1) {
			//msgBuf[len] = 0;				// 也可以不使用memset，但需要在字符串为加'\0',作为字符串结束字符
			cout << "server receive: " << msgBuf;
			SendMsg(msgBuf, len);
		} else {
			break;
		}
	}
	// cout << "The number of connections at this time : " << cltCount << endl;
	WaitForSingleObject(g_hMutex, INFINITE);
	// 处理下线的过程
	for (int i = 0; i < cltCount; i++) {
		if (sockClt == cltSocks[i]) {
			while (i < cltCount) {
				cltSocks[i] = cltSocks[i + 1];
				i++;
			}
			cltCount--;
			break;
		}
	}
	cout << "The number of connections after disconnection: " << cltCount << endl;
	ReleaseMutex(g_hMutex);
	closesocket(sockClt);
	ExitThread(2);	// 结束该线程
	return 0;
}



int main()
{
	WSADATA wsaData{};
	int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != 0) {
		cout << "WSAStartup  error : " << GetLastError() << endl;
		return -1;
	}

	// 检查winsock版本
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		cout << "LOBYTE || HIBYTE error :" << GetLastError() << endl;
		WSACleanup();
		return -1;
	}

	g_hMutex = CreateMutex(NULL, FALSE, NULL);

	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == sockSrv) {
		cout << "socket error：" << GetLastError() << endl;
		return -1;
	}

	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_port = htons(66666);

	if (SOCKET_ERROR == bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(addrSrv))) {
		cout << "bind error：" << GetLastError() << endl;
		return -1;
	}


	if (SOCKET_ERROR == listen(sockSrv, 5)) {
		cout << "listen error：" << GetLastError() << endl;
		return -1;
	}
	cout << "start listening..." << endl;

	SOCKADDR_IN addrClt;
	int len = sizeof(addrClt);
	HANDLE hThread = 0;
	DWORD threadId = 0;
	while (true) {
		SOCKET sockCon = accept(sockSrv, (SOCKADDR*)&addrClt, &len);
		if (INVALID_SOCKET == sockCon) {
			cout << "accept error：" << GetLastError() << endl;
			return -1;
		}
		printf("the client IP is %s, port is %d\n", inet_ntoa(addrClt.sin_addr), ntohs(addrClt.sin_port));

		WaitForSingleObject(g_hMutex, INFINITE);
		// 每成功连接一次客户端，就将其socket套接字插入数组后面,并增加cltCount
		cltSocks[cltCount++] = sockCon;
		ReleaseMutex(g_hMutex);

		cout << "The current number of connections: " << cltCount << endl;
 		
		// 创建一个线程来处理客户端消息
		hThread = CreateThread(NULL, 0, HandleClt, &sockCon, 0, &threadId);
		
	}
	closesocket(sockSrv);
	WSACleanup();
	return 0;
}
