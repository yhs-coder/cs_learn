#pragma once
#include <winsock2.h>
#include <iostream>
using std::cout;
using std::endl;
/*
	recv��send������ ���ڳ������ݵĴ���
*/

int RecvBigData(int sock, char* buf, unsigned int dataSize)
{
	// ѭ������
	unsigned int numsRecv = 0;				// ���յ�������
	unsigned int numsRemaining = dataSize;	// ʣ�ഫ�������
	while (1) {
		int bytesRead = recv(sock, &buf[numsRecv], numsRemaining, 0);
		cout << "bytesRead = " << bytesRead << ", numsRecv = " << numsRecv << ", numsRemaining = " << numsRemaining << endl;

		// �������100M,
		// ������ȫ������
		if (bytesRead == numsRemaining) {
			cout << "All data received completed" << endl;
			return 0;
		} else if (bytesRead > 0) {		//������������
			numsRecv += bytesRead;		// ���� 60	80  100
			numsRemaining -= bytesRead;	// ʣ�� 40   20  0
			continue;	
		} else if (bytesRead < 0 && errno == EAGAIN) { // recv��������
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

		// �������100M,
		// ������ȫ������
		if (bytesSend == numsRemaining) {
			cout << "All data received completed" << endl;
			return 0;
		}
		else if (bytesSend > 0) {		//������������
			numsSend += bytesSend;		// ���� 60	80  100
			numsRemaining -= bytesSend;	// ʣ�� 40   20  0
			continue;
		}
		else if (bytesSend < 0 && errno == EAGAIN) { // recv��������
			continue;
		}
		else {
			return -1;
		}


}

