#pragma once


struct SendPacketHeader
{
	unsigned char Digest[0x14] = { 0 };
	unsigned long long RandomValue;
	int sendCount;
	int dataLength;
	unsigned char dataBuffer[0x2048];
};
struct RecvPacketHeader
{
	unsigned char Digest[0x14] = { 0 };
	unsigned long long RandomValue;
	int recvCount;
	int dataLength;
	unsigned char dataBuffer[0x2048];

};

class secEngine
{
public:
	secEngine();
	~secEngine();
	void setClient(bool state);
	void setServer(bool state);
private:
	bool isClient;
	bool isServer;
	int recvCount;
	int sendCount;
	SendPacketHeader* sph;
	RecvPacketHeader* rph;

};