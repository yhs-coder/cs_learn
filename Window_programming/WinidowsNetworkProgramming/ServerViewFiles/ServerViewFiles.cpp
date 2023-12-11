#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <winsock2.h>

const int MAX = 256;
#pragma comment(lib,"ws2_32.lib")

int main()
{
	// 加载套接字库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	// 初始化套接字库
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		printf("WSAStartup error: %d\n", GetLastError());
		return err;
	}

	// 检查Winsock版本
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		printf("LOBYTE or HIBYTE error: %d\n", GetLastError());
		// 释放在应用程序或DLL中使用的所有Winsock资源
		WSACleanup();
		return -1;
	}


	// 创建套接字
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	if (sockSrv == INVALID_SOCKET) {
		printf("socket error: %d\n", GetLastError());
		return -1;
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
		system("pause");
		return -1;
	}



	SOCKADDR_IN addrClt;	// 客户端
	int len = sizeof(SOCKADDR);

	char msg[MAX];
	memset(msg, 0, MAX);

	while (true) {
		std::cout << "waiting for connection..." << std::endl;
		// 等待并接受客户端的连接请求, 当建立新的连接, 会得到一个新的套接字
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClt, &len);
		if (sockConn == INVALID_SOCKET) {
			printf("listen error: %d\n", GetLastError());
			return -1;
		}

		// 接收数据
		// 打印客户端发送过来的文件内容
		while (recv(sockConn, msg, sizeof(msg), 0) != 0) {
			std::cout << "server msg : " << msg << std::endl;
		}
		
		closesocket(sockConn);
	}
	// 关闭监听套接字，释放所有Winsock资源
	closesocket(sockSrv);
	WSACleanup();
	return 0;

}
