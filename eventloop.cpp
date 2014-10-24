#include "eventloop.h"
EventLoop::EventLoop():active_(NULL)
{

}

EventLoop::~EventLoop()
{
    //
}

void EventLoop::loop()
{
    //get active channels
    poller->poll(&active_);
    for(ChannelList::iterator it = active_.begin();it != active_.end();++it)
    {
        it->handleEvent();
    }
}

void EventLoop::updateChannel(Channel* c)
{
    poller->updateChannel(c);
}
