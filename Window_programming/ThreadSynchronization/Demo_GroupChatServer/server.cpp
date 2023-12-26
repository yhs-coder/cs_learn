#include <windows.h>
#include <iostream>
using namespace std;

/*
	Ⱥ�ķ�������
		- ÿ��һ�����ӵĿͻ��˷�����Ϣ���ͽ���Ϣ���͸������ѽ������ӵĿͻ���
		- ÿ���ͻ�������ʱ����ȥ�����������ߵĿͻ���λ�ã����������λ��ǰ��
		- ���ٽ���Դ�����μ�������
*/

#pragma comment(lib, "ws2_32.lib")
#define MAX_SIZE 5
#define MAX_BUF_SIZE 256

HANDLE g_hMutex = 0;
SOCKET cltSocks[MAX_SIZE] = {0};	// �������ӿͻ��˵�socket����
int cltCount = 0;				// ���ӿͻ��˵�����

void SendMsg(char* msg, size_t len)
{
	WaitForSingleObject(g_hMutex, INFINITE);
	// ����Ϣ���͸��������ӵĿͻ���
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
		memset(msgBuf, 0, sizeof(msgBuf));	// ÿ����һ�Σ�����ջ�����������
		int len = recv(sockClt, msgBuf, sizeof(msgBuf), 0);
		if (len != -1) {
			//msgBuf[len] = 0;				// Ҳ���Բ�ʹ��memset������Ҫ���ַ���Ϊ��'\0',��Ϊ�ַ��������ַ�
			cout << "server receive: " << msgBuf;
			SendMsg(msgBuf, len);
		} else {
			break;
		}
	}
	// cout << "The number of connections at this time : " << cltCount << endl;
	WaitForSingleObject(g_hMutex, INFINITE);
	// �������ߵĹ���
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
	ExitThread(2);	// �������߳�
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

	// ���winsock�汾
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		cout << "LOBYTE || HIBYTE error :" << GetLastError() << endl;
		WSACleanup();
		return -1;
	}

	g_hMutex = CreateMutex(NULL, FALSE, NULL);

	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == sockSrv) {
		cout << "socket error��" << GetLastError() << endl;
		return -1;
	}

	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_port = htons(66666);

	if (SOCKET_ERROR == bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(addrSrv))) {
		cout << "bind error��" << GetLastError() << endl;
		return -1;
	}


	if (SOCKET_ERROR == listen(sockSrv, 5)) {
		cout << "listen error��" << GetLastError() << endl;
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
			cout << "accept error��" << GetLastError() << endl;
			return -1;
		}
		printf("the client IP is %s, port is %d\n", inet_ntoa(addrClt.sin_addr), ntohs(addrClt.sin_port));

		WaitForSingleObject(g_hMutex, INFINITE);
		// ÿ�ɹ�����һ�οͻ��ˣ��ͽ���socket�׽��ֲ����������,������cltCount
		cltSocks[cltCount++] = sockCon;
		ReleaseMutex(g_hMutex);

		cout << "The current number of connections: " << cltCount << endl;
 		
		// ����һ���߳�������ͻ�����Ϣ
		hThread = CreateThread(NULL, 0, HandleClt, &sockCon, 0, &threadId);
		
	}
	closesocket(sockSrv);
	WSACleanup();
	return 0;
}
