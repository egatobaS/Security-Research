#include "pch.h"


void CreateClientThread(SOCKET Client, void* lpThreadEntry)
{
#if defined(_WIN32)
	HANDLE OfThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)lpThreadEntry, (LPVOID)Client, 0, 0);
	CloseHandle(OfThread);
#else
	pthread_create(&Client->Thread, NULL, (void*(*)(void*))lpThreadEntry, Client);
	pthread_detach(Client->Thread);
#endif
}
