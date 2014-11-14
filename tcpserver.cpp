#include "tcpserver.h"
#include "eventloop.h"
#include "acceptor.h"
#include "tcpconnection.h"
#include <boost/bind.hpp>
#include <iostream>
#include <stdio.h>

TcpServer::TcpServer(EventLoop* loop,bool loopbackOnly,unsigned short port):\
    acceptor_(new Acceptor(loop,loopbackOnly,port)),loop_(loop),connIndex_(1)
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
    std::cout<<"xnew connection from peer:"<<inet_ntoa(addr.sin_addr)<<" ["<<addr.sin_port<<"] \n";
    
    char buff[128] = {0};
    snprintf(buff,sizeof(buff),buff,"%s#%d",inet_ntoa(addr.sin_addr),connIndex_++);
    std::string name(buff);
    TcpConnection* conn = new TcpConnection(loop_,fd,addr,addr);
    connMap_[std::string(buff)] = conn;
    //some callbacks
    //remove from connMap
    //conn->setCloseCallback();
    currentLoop()->runInLoop(boost::bind(&TcpConnection::connEstablished,conn));
}

void TcpServer::start()
{
    acceptor_->listen();
}
