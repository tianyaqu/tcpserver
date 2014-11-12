#include "tcpconnection.h"
#include "channel.h"
#include "eventloop.h"


TcpConnection::TcpConnection(EventLoop* loop,int fd,\
    const struct sockaddr_in& self,const struct sockaddr_in& peer):loop_(loop),\
    channel_(new Channel(loop,fd)),sockFd_(fd),self_(self),peer_(peer),state_(kConnecting)
{
    channel_->registerReadCallback(boost::bind(&TcpConnection::handleRead,this));
    channel_->registerWriteCallback(boost::bind(&TcpConnection::handleWrite,this));
    //channel_->registerCloseCallback(boost::bind(&TcpConnection::handleClose,this));
}

TcpConnection::~TcpConnection()
{
}

void TcpConnection::connEstablished()
{
    //assert(state_ == kConnecting);
    setState(kConnected);
    channel_->enableRead();
    //some callbacks
    //callback_();
}

void TcpConnection::handleRead()
{
    //read to buffer
    //read(buffer,size,channel_->getFd);
    //some callbacks for example logical process
    //logicalCallback_();
}

void TcpConnection::handleWrite()
{
}

void TcpConnection::handleClose()
{
}
