#include "pch.h"

secEngine::secEngine()
{
	this->sph = NULL;
	this->rph = NULL;
	this->recvCount = 0;
	this->sendCount = 0;
	this->isClient = false;
	this->isServer = false;
}

secEngine::~secEngine()
{

}

void secEngine::setClient(bool state)
{
	this->isClient = state;
}

void secEngine::setServer(bool state)
{
	this->isServer = state;
}
