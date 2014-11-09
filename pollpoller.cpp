#include "pollpoller.h"
#include "channel.h"
#include <poll.h>

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
        fd.events = c->getEvent();
        fd.revents = 0;
        fdSet_.push_back(fd);

        int index = static_cast<int>(fdSet_.size()) - 1;
        c->setIndex(index);
        channelMap_[fd.fd] = c;
    }
    else //update an existing channel
    {
        unsigned int index = c->getIndex();
        struct pollfd& fd = fdSet_[index];
        fd.events = c->getEvent();
        fd.revents = 0;
    }
}

void Poller::removeChannel(Channel* c)
{
    int index = c->getIndex();
    int fd = fdSet_.back().fd;
    iter_swap(fdSet_.begin()+index, fdSet_.end()-1);

    channelMap_[fd]->setIndex(index);
    fdSet_.pop_back();
}

void Poller::poll(ChannelList* list)
{
}
