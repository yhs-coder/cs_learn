#pragma once
#include <winsock2.h>
#include <iostream>
using std::cout;
using std::endl;
/*
	recv和send函数： 关于超大数据的传输
*/

int RecvBigData(int sock, char* buf, unsigned int dataSize)
{
	// 循环接收
	unsigned int numsRecv = 0;				// 接收到的数据
	unsigned int numsRemaining = dataSize;	// 剩余传输的数据
	while (1) {
		int bytesRead = recv(sock, &buf[numsRecv], numsRemaining, 0);
		cout << "bytesRead = " << bytesRead << ", numsRecv = " << numsRecv << ", numsRemaining = " << numsRemaining << endl;

		// 假设接收100M,
		// 数据已全部接收
		if (bytesRead == numsRemaining) {
			cout << "All data received completed" << endl;
			return 0;
		} else if (bytesRead > 0) {		//继续接收数据
			numsRecv += bytesRead;		// 接收 60	80  100
			numsRemaining -= bytesRead;	// 剩余 40   20  0
			continue;	
		} else if (bytesRead < 0 && errno == EAGAIN) { // recv函数出错
			continue;
		} else {
			return -1;
		}

	}
}


int SendBigData(int sock, unsigned char* buf, unsigned dataSize)
{
	unsigned int numsSend = 0;
	unsigned int numsRemaining = dataSize;
	while (1) {
		int bytesSend = send(sock, &buf[numsSend], numsRemaining, 0);
		cout << "bytesRead = " << bytesSend << ", numsSend = " << numsSend << ", numsRemaining = " << numsRemaining << endl;

		// 假设接收100M,
		// 数据已全部接收
		if (bytesSend == numsRemaining) {
			cout << "All data received completed" << endl;
			return 0;
		}
		else if (bytesSend > 0) {		//继续接收数据
			numsSend += bytesSend;		// 接收 60	80  100
			numsRemaining -= bytesSend;	// 剩余 40   20  0
			continue;
		}
		else if (bytesSend < 0 && errno == EAGAIN) { // recv函数出错
			continue;
		}
		else {
			return -1;
		}


}

