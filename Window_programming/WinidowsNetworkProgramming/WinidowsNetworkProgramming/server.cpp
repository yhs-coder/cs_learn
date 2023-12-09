#include <iostream>
#include <winsock2.h>
#include <cctype>

// VSʹ��inet_ntoa()��������Ľ������
// #pragma warning(disable:4996)

// ��������Windows Sockets��,������ļ�������Windows Sockets API������ʵ�֡�
// �����ʼ���׽��ֿ�
#pragma comment(lib,"ws2_32.lib")

int main()
{
	// �����׽��ֿ�
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	// MAKEWORD(1, 1)��һ���궨�壬��ʾʹ��Winsock 1.1�汾
	wVersionRequested = MAKEWORD(1, 1);

	// ��ʼ���׽��ֿ�
	err = WSAStartup(wVersionRequested, &wsaData);
	// ��ʼ��ʧ�ܷ���-1
	if (err != 0) {
		printf("WSAStartup error: %d\n", GetLastError());
		return err;
	}

	// ���Winsock�汾
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		printf("LOBYTE or HIBYTE error: %d\n", GetLastError());
		// �ͷ���Ӧ�ó����DLL��ʹ�õ�����Winsock��Դ
		WSACleanup();
		return - 1;
	}


	// �����׽���
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	if (sockSrv == INVALID_SOCKET) {
		printf("socket error: %d\n", GetLastError());
		return - 1;
	}


	// ��ʼ��SOCKADDR_IN�ṹ���У�Ҫ�󶨵�IP�Ͷ˿���Ϣ
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	// INADDR_ANY����������IP����Ҫת���������ֽ��򣡣�
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(9999);

	// ���׽��ֺͱ��ص�IP��˿ڽ��а� 
	if (SOCKET_ERROR == bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(addrSrv))) {
		printf("bind error: %d\n", GetLastError());
		return -1;
	}

	// ���������׽������ü��������������������
	if (SOCKET_ERROR == listen(sockSrv, 6)) {
		printf("listen error: %d\n", GetLastError());
		return -1;
	}
	

	SOCKADDR_IN addrClt;	// �ͻ���
	int len = sizeof(SOCKADDR);

	std::cout << "waiting for connection..." << std::endl;
	// �ȴ������ܿͻ��˵���������, �������µ�����, ��õ�һ���µ��׽���
	SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClt, &len);
	if (sockConn == INVALID_SOCKET) {
		printf("listen error: %d\n", GetLastError());
		return -1;
	}

	// ��ӡ�ͻ��˵ĵ�ַ��Ϣ
	printf("client IP: %s, port: %d\n", inet_ntoa(addrClt.sin_addr), ntohs(addrClt.sin_port));

#if 1
	// ��ͻ���ѭ��ͨ��
	while (true) {
		// ��������
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
	// ƥ��Ϳͻ���ͨ��һ��
	while (true) {
		char sendBuf[256] = { 0 };
		sprintf_s(sendBuf, 256, "server say: The client IP is %s...\n", inet_ntoa(addrClt.sin_addr));
		// ��������
		if (send(sockConn, sendBuf, strlen(sendBuf) + 1, 0) == SOCKET_ERROR) {
			printf("listen error: %d\n", GetLastError());
			continue;
		}	
		char recvBuf[256] = { 0 };
		Sleep(5000);
		// ��������
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

	// �رռ����׽��֣��ͷ�����Winsock��Դ
	closesocket(sockSrv);
	WSACleanup();
	return 0;
}
