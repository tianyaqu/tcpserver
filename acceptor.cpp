#include "eventloop.h"
#include "acceptor.h"
#include <netinet/in.h>
#include <netinet/tcp.h>

static const in_addr_t kInaddrAny = INADDR_ANY;
static const in_addr_t kInaddrLoopback = INADDR_LOOPBACK;

Acceptor::Acceptor(EventLoop *loop,bool loopbackOnly,unsigned short port)
{
    //make socket
    int listenFd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (listenFd < 0)
    {
        std::cout<<"error in generate listen socket\n";
    }

    //innet addr;
    struct sockaddr_in innetAddr;
    bzero(&innetAddr,sizeof(innetAddr);
    innetAddr.sin_family = AF_INET;
    in_addr_t ip = loopbackOnly ? kInaddrLoopback : kInaddrAny;
    innetAddr.sin_addr.s_addr = htobe32(ip);
    innetAddr.sin_port = htobe16(port);

    int ret = ::bind(listenFd,sockAddr,sizeof(sockAddr));
    if(ret < 0)
    {
        std::cout<<"error in bind listen socket\n";
    }

    accpChannel_ = new Channel(loop,listenFd);
}

void Acceptor::listen()
{
    acceptChannel_->registerReadCallback(boost::bind(Acceptor::onRead,this));
    acceptChannel_->enableRead();
}

void Acceptor::onRead()
{
}
