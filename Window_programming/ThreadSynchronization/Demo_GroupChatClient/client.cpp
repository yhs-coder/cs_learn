#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
using namespace std;
/*
	�ͻ����������飺
	1. �ȴ�����˿������񲢽�������
	2. ������Ϣ���ȴ��û�������̨������Ϣ��Ȼ���͸������ ���ͻ��� + ��Ϣ��
	3. �ͻ��˵ȴ�����˵���Ϣ�������������ͻ��˵���Ϣ
	4. �ͻ��������˳����ӣ�������
*/

#pragma comment(lib, "ws2_32.lib")
#define MAX_NAME_SIZE 128
#define MAX_BUF_SIZE 256

char szName[MAX_NAME_SIZE] = "[default]"; // �ͻ������� 
char szMsg[MAX_BUF_SIZE] = { 0 };	// �շ����ݵĻ�����


DWORD CALLBACK SendMsg(LPVOID lpParam)
{
	SOCKET conSock = *((SOCKET*)lpParam);
	char szNameMsg[MAX_BUF_SIZE + MAX_NAME_SIZE] = { 0 };	// �洢�ͻ���������Ϣ
	int len = 0;
	while (1) {
		memset(szMsg, 0, MAX_BUF_SIZE);		// ������ݻ�����
		fgets(szMsg, MAX_BUF_SIZE, stdin);
		// cout << "strlen(szMsg) = " << strlen(szMsg) << endl;  // �����ַ���ʱ��\n�س���Ҳ������һ���ַ�
		if (!strcmp(szMsg, "Q\n") || !strcmp(szMsg, "q\n")) {
			cout << "Client actively disconnects..." << endl;
			closesocket(conSock);
			exit(0);
		}
		// ƴ����Ϣ
		sprintf(szNameMsg, "[%s]: %s", szName, szMsg);
		send(conSock, szNameMsg, strlen(szNameMsg), 0);
	}
}

DWORD CALLBACK RecvMsg(LPVOID lpParam)
{
	SOCKET conSock = *((SOCKET*)lpParam);
	char szNameMsg[MAX_BUF_SIZE + MAX_NAME_SIZE] = { 0 };	// �洢�ͻ���������Ϣ
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
	// �ӿ���̨����ͻ�����
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
		cout << "socket error��" << GetLastError() << endl;
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

