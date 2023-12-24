#include <iostream>
#include <winsock2.h>

// VS使用inet_ntoa()产生错误的解决方法
#pragma warning(disable:4996)

// 用于链接Windows Sockets库,这个库文件包含了Windows Sockets API函数的实现。
// 必须初始化套接字库
#pragma comment(lib,"ws2_32.lib")


int main()
{

	// 初始化套接字库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		printf("WSAStartup errorNum = %d\n", GetLastError());
		return err;
	}
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		printf("LOBYTE or BIBYTE error = %d\n", GetLastError());
		WSACleanup();
		return -1;
	}

	SOCKET sockClt = socket(AF_INET, SOCK_STREAM, 0);
	if (sockClt == INVALID_SOCKET) {
		printf("socket error: %d\n", GetLastError());
		return -1;
	}
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.189.1");
	addr.sin_port = htons(9999);
	// 进行连接
	if (connect(sockClt, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
		printf("connect error: %d\n", GetLastError());
		return -1;
	}
#if 0
	// 与服务端循环通信
	while (true) {
		char sendBuf[256] = { 0 };
		std::cin >> sendBuf;
		send(sockClt, sendBuf, strlen(sendBuf) + 1, 0);

		char recvBuf[256] = { 0 };
		int len = recv(sockClt, recvBuf, sizeof(recvBuf), 0);
		if (len == SOCKET_ERROR) {
			printf("recv error: %d\n", GetLastError());
			return -1;
		} else if (len == 0) {
			std::cout << "the server disconnected..." << std::endl;
			closesocket(sockClt);
			return -1;
		} else {
			std::cout << recvBuf << std::endl;
		}
		
	}
#else
	// 和服务端只进行一次通信
	std::cout << "client connected..." << std::endl;
	// 接收数据
	char recvBuf[256] = { 0 };
	int len = recv(sockClt, recvBuf, sizeof(recvBuf), 0);
	if (len == SOCKET_ERROR) {
		printf("recv error: %d\n", GetLastError());
		return -1;
	}
	else if (len == 0) {
		std::cout << "the server disconnected..." << std::endl;
		return -1;
	}
	else {
		std::cout << recvBuf << std::endl;
	}
	// 阻塞一下，验证服务端是否可以处理多个客户端
	std::cout << "getchar..." << std::endl;
	getchar();

	// 发送数据
	char sendBuf[256] = { 0 };
	sprintf_s(sendBuf, 256, "client say: hello, server... \n");
	send(sockClt, sendBuf, strlen(sendBuf) + 1, 0);
	
#endif

	closesocket(sockClt);
	WSACleanup();
	system("pause");
	return 0;
}
