#include <iostream>
#include <winsock2.h>
#include <cctype>

// VS使用inet_ntoa()产生错误的解决方法
// #pragma warning(disable:4996)

// 用于链接Windows Sockets库,这个库文件包含了Windows Sockets API函数的实现。
// 必须初始化套接字库
#pragma comment(lib,"ws2_32.lib")

int main()
{
	// 加载套接字库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	// MAKEWORD(1, 1)是一个宏定义，表示使用Winsock 1.1版本
	wVersionRequested = MAKEWORD(1, 1);

	// 初始化套接字库
	err = WSAStartup(wVersionRequested, &wsaData);
	// 初始化失败返回-1
	if (err != 0) {
		printf("WSAStartup error: %d\n", GetLastError());
		return err;
	}

	// 检查Winsock版本
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		printf("LOBYTE or HIBYTE error: %d\n", GetLastError());
		// 释放在应用程序或DLL中使用的所有Winsock资源
		WSACleanup();
		return - 1;
	}


	// 创建套接字
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	if (sockSrv == INVALID_SOCKET) {
		printf("socket error: %d\n", GetLastError());
		return - 1;
	}


	// 初始化SOCKADDR_IN结构体中，要绑定的IP和端口信息
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	// INADDR_ANY：接受任意IP，需要转换成网络字节序！！
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(9999);

	// 将套接字和本地的IP与端口进行绑定 
	if (SOCKET_ERROR == bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(addrSrv))) {
		printf("bind error: %d\n", GetLastError());
		return -1;
	}

	// 给监听的套接字设置监听，并设置最大连接数
	if (SOCKET_ERROR == listen(sockSrv, 6)) {
		printf("listen error: %d\n", GetLastError());
		return -1;
	}
	

	SOCKADDR_IN addrClt;	// 客户端
	int len = sizeof(SOCKADDR);

	std::cout << "waiting for connection..." << std::endl;
	// 等待并接受客户端的连接请求, 当建立新的连接, 会得到一个新的套接字
	SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClt, &len);
	if (sockConn == INVALID_SOCKET) {
		printf("listen error: %d\n", GetLastError());
		return -1;
	}

	// 打印客户端的地址消息
	printf("client IP: %s, port: %d\n", inet_ntoa(addrClt.sin_addr), ntohs(addrClt.sin_port));

#if 1
	// 与客户端循环通信
	while (true) {
		// 接收数据
		char recvBuf[256] = { 0 };
		std::cout << "begin recv..." << std::endl;
		int len = recv(sockConn, recvBuf, sizeof(recvBuf), 0);
		std::cout << "end recv..." << std::endl;
		if (len == SOCKET_ERROR) {
			printf("recv error: %d\n", GetLastError());
			return -1;
		}
		else if (len == 0) {
			std::cout << "the client disconnected..." << std::endl;
			closesocket(sockConn);
			return -1;
		}
		else {
			std::cout << recvBuf << std::endl;
		}

		for (int i = 0; i < len; i++) {
			recvBuf[i] = toupper(recvBuf[i]);
		}
		std::cout << recvBuf << std::endl;
		send(sockConn, recvBuf, strlen(recvBuf), 0);
	}

#else
	// 匹配和客户端通信一次
	while (true) {
		char sendBuf[256] = { 0 };
		sprintf_s(sendBuf, 256, "server say: The client IP is %s...\n", inet_ntoa(addrClt.sin_addr));
		// 发送数据
		if (send(sockConn, sendBuf, strlen(sendBuf) + 1, 0) == SOCKET_ERROR) {
			printf("listen error: %d\n", GetLastError());
			continue;
		}	
		char recvBuf[256] = { 0 };
		Sleep(5000);
		// 接收数据
		int len = recv(sockConn, recvBuf, sizeof(recvBuf), 0);
		if (len == SOCKET_ERROR) {
			printf("recv error: %d\n", GetLastError());
			return -1;
		}
		else if (len == 0) {
			std::cout << "the client disconnected..." << std::endl;
			closesocket(sockConn);
			return -1;
		}
		else {
			std::cout << recvBuf << std::endl;
		}
		closesocket(sockConn);
	}
#endif

	// 关闭监听套接字，释放所有Winsock资源
	closesocket(sockSrv);
	WSACleanup();
	return 0;
}
