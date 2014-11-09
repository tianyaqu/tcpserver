#include "channel.h"
#include "eventloop.h"

Channel::Channel(EventLoop* loop,int fd):loop_(loop),readCallback_(NULL),writeCallback_(NULL),events_(0),fd_(fd)
{
}

Channel::~Channel()
{

}

void Channel::update()
{
    loop_->updateChannel(this);
}

void Channel::registerReadCallback(const Callback& r)
{
    readCallback_ = r;
}

void Channel::registerWriteCallback(const Callback& w)
{
    writeCallback_ = w;
}

void Channel::handleEvent()
{
    if(events_ & (POLLIN | POLLPRI))
    {
        if(readCallback_)
        {
            readCallback_();
        }
    }

    if(events_ & POLLOUT)
    {
        if(writeCallback_)
        {
            writeCallback_();
        }
    }
}
