#include <iostream>
#include <winsock2.h>

// VSʹ��inet_ntoa()��������Ľ������
#pragma warning(disable:4996)

// ��������Windows Sockets��,������ļ�������Windows Sockets API������ʵ�֡�
// �����ʼ���׽��ֿ�
#pragma comment(lib,"ws2_32.lib")


int main()
{

	// ��ʼ���׽��ֿ�
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
	// ��������
	if (connect(sockClt, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
		printf("connect error: %d\n", GetLastError());
		return -1;
	}
#if 0
	// ������ѭ��ͨ��
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
	// �ͷ����ֻ����һ��ͨ��
	std::cout << "client connected..." << std::endl;
	// ��������
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
	// ����һ�£���֤������Ƿ���Դ������ͻ���
	std::cout << "getchar..." << std::endl;
	getchar();

	// ��������
	char sendBuf[256] = { 0 };
	sprintf_s(sendBuf, 256, "client say: hello, server... \n");
	send(sockClt, sendBuf, strlen(sendBuf) + 1, 0);
	
#endif

	closesocket(sockClt);
	WSACleanup();
	system("pause");
	return 0;
}
