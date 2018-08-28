#include <stdio.h>
#include <string.h>

#ifdef __WIN32
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include "socket.h"
#include "logoutput.h"

namespace cura
{
    
#ifdef __WIN32
bool wsaStartupDone = false;
#endif

ClientSocket::ClientSocket()
{
    sockfd = -1;

}

void ClientSocket::connectTo(std::string host, int port)
{

}

ClientSocket::~ClientSocket()
{
    close();
}

void ClientSocket::sendInt32(int32_t nr)
{

}

void ClientSocket::sendFloat32(float f)
{

}


void ClientSocket::sendAll(const void* data, int length)
{

}

int32_t ClientSocket::recvInt32()
{

}

float ClientSocket::recvFloat32()
{

}

void ClientSocket::recvAll(void* data, int length)
{

}

void ClientSocket::close()
{
    sockfd = -1;
}

}//namespace cura
