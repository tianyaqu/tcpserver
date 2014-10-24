#include "pollpoller.h"
#include "channel.h"

Poller::Poller()
{
}

Poller::~Poller()
{
}

void Poller::updateChannel(Channel* c)
{
    //new channel
    if(c->getIndex() < 0)
    {
        struct pollfd fd;
        fd.fd = c->getFd();
        fd.event = c->getEvent();
        fd.revent = 0;
        fdSet_.pushback(fd);

        int index = static_cast<int>(fdSet.size()) - 1;
        c->setIndex(index);
        channelMap_[fd.fd] = c;
    }
    else //update an existing channel
    {
        unsigned int index = c->getIndex();
        struct pollfd& fd = fdSet_[index];
        fd.event = c->getEvent();
        fd.revent = 0;
    }
}

void Poller::removeChannel(Channel* c)
{
    int index = c->getIndex();
    int fd = fdSet_.back().fd;
    iter_swap(fdSet_.begin()+index, fdSet_.end()-1);

    channelMap_[fd]->setIndex(index);
    fdSet_.popback();
}
