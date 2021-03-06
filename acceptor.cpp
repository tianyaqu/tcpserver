#include "eventloop.h"
#include "acceptor.h"
#include "channel.h"
#include <iostream>
#include <strings.h>
#include <boost/bind.hpp>

static const in_addr_t kInaddrAny = INADDR_ANY;
static const in_addr_t kInaddrLoopback = INADDR_LOOPBACK;

Acceptor::Acceptor(EventLoop *loop,bool loopbackOnly,unsigned short port)
{
    //make socket
    listenFd_ = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (listenFd_ < 0)
    {
        std::cout<<"error in generate listen socket\n";
    }

    //innet addr;
    struct sockaddr_in innetAddr;
    bzero(&innetAddr,sizeof(innetAddr));
    innetAddr.sin_family = AF_INET;
    in_addr_t ip = loopbackOnly ? kInaddrLoopback : kInaddrAny;
    innetAddr.sin_addr.s_addr = htobe32(ip);
    innetAddr.sin_port = htobe16(port);

    int ret = ::bind(listenFd_,(struct sockaddr*)&innetAddr,sizeof(innetAddr));
    if(ret < 0)
    {
        std::cout<<"error in bind listen socket\n";
    }

    acceptChannel_ = new Channel(loop,listenFd_);
}

Acceptor::~Acceptor()
{
    ::close(listenFd_);
}

void Acceptor::listen()
{
    int ret = ::listen(listenFd_,SOMAXCONN);
    if(ret < 0 )
    {
        std::cout<<"listen failed\n";
    }
    acceptChannel_->registerReadCallback(
        boost::bind(&Acceptor::onRead,this));
    acceptChannel_->enableRead();
}

void Acceptor::onRead()
{
    struct sockaddr_in peerAddr;
    socklen_t len = static_cast<socklen_t>(sizeof(struct sockaddr_in));
    int connfd = ::accept(listenFd_,(struct sockaddr*)&peerAddr,&len);

    if(connfd >= 0)
    {
        // connection dealing procedures
        if(newConnCallback_)
        {
            newConnCallback_(connfd,peerAddr);
        }
    }

}
void Acceptor::setNewConnCallback(const NewConnCallback& cb)
{
    newConnCallback_ = cb;
}
