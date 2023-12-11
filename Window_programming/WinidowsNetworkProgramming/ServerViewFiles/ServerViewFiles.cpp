#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <winsock2.h>

const int MAX = 256;
#pragma comment(lib,"ws2_32.lib")

int main()
{
	// �����׽��ֿ�
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	// ��ʼ���׽��ֿ�
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		printf("WSAStartup error: %d\n", GetLastError());
		return err;
	}

	// ���Winsock�汾
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		printf("LOBYTE or HIBYTE error: %d\n", GetLastError());
		// �ͷ���Ӧ�ó����DLL��ʹ�õ�����Winsock��Դ
		WSACleanup();
		return -1;
	}


	// �����׽���
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	if (sockSrv == INVALID_SOCKET) {
		printf("socket error: %d\n", GetLastError());
		return -1;
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
		system("pause");
		return -1;
	}



	SOCKADDR_IN addrClt;	// �ͻ���
	int len = sizeof(SOCKADDR);

	char msg[MAX];
	memset(msg, 0, MAX);

	while (true) {
		std::cout << "waiting for connection..." << std::endl;
		// �ȴ������ܿͻ��˵���������, �������µ�����, ��õ�һ���µ��׽���
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClt, &len);
		if (sockConn == INVALID_SOCKET) {
			printf("listen error: %d\n", GetLastError());
			return -1;
		}

		// ��������
		// ��ӡ�ͻ��˷��͹������ļ�����
		while (recv(sockConn, msg, sizeof(msg), 0) != 0) {
			std::cout << "server msg : " << msg << std::endl;
		}
		
		closesocket(sockConn);
	}
	// �رռ����׽��֣��ͷ�����Winsock��Դ
	closesocket(sockSrv);
	WSACleanup();
	return 0;

}
