#include "tcpconnection.h"
#include "channel.h"
#include "eventloop.h"
#include <assert.h>
#include <boost/bind.hpp>
#include <stdio.h>

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
    assert(state_ == kConnecting);
    setState(kConnected);
    //some callbacks
    //callback_();
    channel_->registerReadCallback(boost::bind(&TcpConnection::handleRead,this));
    channel_->registerWriteCallback(boost::bind(&TcpConnection::handleWrite,this));
    //channel_->registerCloseCallback(boost::bind(&TcpConnection::handleClose,this));
    channel_->enableRead();
}

void TcpConnection::connClosed()
{
}

void TcpConnection::handleRead()
{
    //read to buffer
    char buffer[1500] = {0};
    char *data;
    int len = read(channel_->getFd(),buffer,sizeof(buffer));
    if(len > 0)
    {
        printf("%s\n",buffer);
        //char buf[120] = "HTTP/1.1 200 OK\r\nContent-Length: Content-Type: text/html\r\r<html>hello world</html>"; 
        char buf[120] = "<html>hello world</html>";
        char buff[256] = {0};
        snprintf(buff,sizeof(buff),"%s%s%d\r\n\r\n%s","HTTP/1.1 200 OK\r\n","Content-Length: ",strlen(buf),buf);
        ::write(channel_->getFd(),buff,63);
    }
    else if(len == 0)
    {
    }
    else
    {
    }
    ::close(channel_->getFd());
    //strip(buffer,&data);
    //some callbacks for example logical process
    //logicalCallback_(data);
}

void TcpConnection::handleWrite()
{
}

void TcpConnection::handleClose()
{
}
