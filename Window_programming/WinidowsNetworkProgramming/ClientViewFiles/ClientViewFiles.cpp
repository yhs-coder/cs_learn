#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
using std::cout;
using std::endl;

#pragma comment(lib,"ws2_32.lib")


int SendToServer(const char* path)
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

	// �ͷ����ֻ����һ��ͨ��
	std::cout << "client connected..." << std::endl;

	// ��ȡ�ļ�����
	char sendBuf[256] = { 0 };
	FILE* fp = fopen(path, "rb");
	int len = fread(sendBuf, 1024, 1,fp);
	if (len < 0) {
		cout << "fread error:" << GetLastError();
		return -1;
	}
	// ��������	
	send(sockClt, sendBuf, strlen(sendBuf) + 1, 0);
	closesocket(sockClt);
	WSACleanup();
	return 0;

}

// �鿴��Ŀ¼�µ��ļ��������ļ����͵����ݷ��͵������
void ViewFiles(const char* dirPath)
{
	// ������·��path�����е��ļ�
	WIN32_FIND_DATA filesData;
	HANDLE hFile; // �þ������ʶ�ļ�

	char szFilePath[MAX_PATH] = { 0 }; // MAX_PATH ��ʾ�ļ�·������󳤶�
	strcpy(szFilePath, dirPath);
	strcat(szFilePath, "\\*"); // �����*��ƥ�����е��ļ�������������ҵ���һ���ļ�

	// ���Ҳ����ص�һ���ļ����
	hFile = FindFirstFile(szFilePath, &filesData);

	// �������е��ļ�
	do 
	{
		char path[256] = { 0 };
		strcpy(path, dirPath);
		strcat(path, "\\");
		strcat(path, filesData.cFileName);
		cout << path << endl;
		// ����ļ�������txt�����͸��ļ������ݵ������
		if (strstr(path, ".txt")) {
			SendToServer(path);
		}

	} while (FindNextFile(hFile, &filesData)); // FindNextFile�Ҳ����¸��ļ�����NULL
	cout << "�����ļ��о����..." << endl;
}



int main()
{
	ViewFiles("D:\\test");
	system("pause");
	return 0;
}