#include <stdio.h>
#include <string.h>

#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/types.h>
#include <unistd.h>

#endif

#include "socket.h"
#include "logoutput.h"

#ifdef WIN32
bool wsaStartupDone = false;
#endif

ClientSocket::ClientSocket()
{
    sockfd = -1;

#ifdef WIN32

#endif
}

void ClientSocket::connectTo(std::string host, int port)
{

}

ClientSocket::~ClientSocket()
{
    close();
}

void ClientSocket::sendNr(int nr)
{
    sendAll(&nr, sizeof(int));
}

void ClientSocket::sendAll(const void* data, int length)
{

}

int ClientSocket::recvNr()
{
    int ret = 0;
    recvAll(&ret, 4);
    return ret;
}

void ClientSocket::recvAll(void* data, int length)
{

}

void ClientSocket::close()
{

}
