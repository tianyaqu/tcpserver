#include "tcpserver.h"
#include "eventloop.h"
#include "acceptor.h"
#include <boost/bind.hpp>
#include <iostream>

TcpServer::TcpServer(EventLoop* loop,bool loopbackOnly,unsigned short port):\
    acceptor_(new Acceptor(loop,loopbackOnly,port)),loop_(loop)
{
    acceptor_->setNewConnCallback(boost::bind(&TcpServer::OnConnection,this,_1,_2));
}

TcpServer::~TcpServer()
{
    delete acceptor_;
}

void TcpServer::OnConnection(int fd,const struct sockaddr_in& addr)
{
    sockaddr tmp;
    std::cout<<"new connection from peer:"<<inet_ntoa(addr.sin_addr)<<" ["<<addr.sin_port<<"] \n";
}

void TcpServer::start()
{
    acceptor_->listen();
}
