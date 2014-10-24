#include "tcpserver.h"
#include "eventloop.h"
#include "acceptor.h"

TcpServer::TcpServer(EventLoop* loop,bool loopbackOnly,unsigned short port):\
acceptor_(new Acceptor(loop,loopbackOnly,port)),loop_(loop)
{
}

TcpServer::~TcpServer()
{
}

void TcpServer::onConnection()
{
}

void TcpServer::start()
{
    acceptor_->listen();
}
