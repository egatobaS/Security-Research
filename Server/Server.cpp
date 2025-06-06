#include "pch.h"

struct Header
{
	int dataSize;
	unsigned char timeChecksum[0x14];
};

struct Data : Header
{
	unsigned char lotsOfData[0x200];
};

std::time_t bruteForceStamp(Header* Header, int size)
{
	unsigned char localTimeDigest[0x14] = { 0 };

	unsigned char* realDataBuffer = (unsigned char*)Header;

	std::time_t time_now = std::time(nullptr);
	std::time_t guessedTime = 0;

	for (int i = 0; i < 10; i++)
	{
		memset(localTimeDigest, 0, 0x14);

		unsigned long long tempValue = 0;

		guessedTime = time_now - i;

		for (int i = 0; i < size; i++)
			tempValue += (realDataBuffer[i] ^ guessedTime) % 255;

		sha1(&tempValue, 4, localTimeDigest);

		if (!memcmp(localTimeDigest, Header->timeChecksum, 0x14))
			break;
	}



	return guessedTime;
}

void ClientThread(int* lpParameters)
{
	unsigned char PacketData[4096] = { 0 };

	Sockets Client((SOCKET)lpParameters);

	if (Client.Receive((char*)PacketData, 4096))
	{
		std::time_t timeOnClient = bruteForceStamp((Header*)PacketData, sizeof(Header) - 0x14);

		printf("Time on the client is supposed to be %lli\n", timeOnClient);

	}
	Client.Close();
}

int main()
{
	WSADATA wsaData = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	Sockets* Connection = new Sockets((unsigned short)1337);

	if (Connection->StartListener(10000)) {

		struct sockaddr_in addr;

		SOCKET Socket = 0;

		for (;;)
		{
			int Lenght = sizeof(addr);

			Socket = Connection->Accept((struct sockaddr *)&addr, &Lenght);

			CreateClientThread(Socket, (void*)ClientThread);
		}
	}

	delete Connection;

	printf("Hi, I am the server\n");

	system("pause");
	return 0;
}