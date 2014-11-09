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
        struct pollfd pfd;
        pfd.fd = c->getFd();
        pfd.events = c->getEvent();
        pfd.revents = 0;
        fdSet_.push_back(pfd);

        int index = static_cast<int>(fdSet_.size()) - 1;
        c->setIndex(index);
        channelMap_[pfd.fd] = c;
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
    int result = ::poll((struct pollfd*)&fdSet_[0],fdSet_.size(),10000);
    if(result > 0)
    {
        //fill the channelList
        fillActiveChannels(list);

    }
    else if(result == 0)
    {
        //nothing happend
    }
    else
    {
        //probably wrong
    }
}

void Poller::fillActiveChannels(ChannelList* list) const
{
    for(PollFdList::const_iterator it = fdSet_.begin();it < fdSet_.end();it++)
    {
        if(it->revents > 0)
        {
            ChannelMap::const_iterator ch = channelMap_.find(it->fd);
            assert(ch != channelMap_.end());
            Channel* c = ch->second;
            assert(c->getFd() == it->fd);
            c->set_revents(it->revents);
            list->push_back(c);
        }
    }
}
