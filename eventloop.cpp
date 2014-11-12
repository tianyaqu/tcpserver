#include "eventloop.h"
#include "pollpoller.h"
#include "channel.h"

EventLoop::EventLoop():poller_(new Poller()),quit_(false)
{
}

EventLoop::~EventLoop()
{
    //
}

void EventLoop::loop()
{
    while(!quit_)
    {
        //get active channels
        poller_->poll(&active_);
        for(ChannelList::iterator it = active_.begin();it != active_.end();++it)
        {
            (*it)->handleEvent();
        }
    }
}

void EventLoop::updateChannel(Channel* c)
{
    poller_->updateChannel(c);
}

void EventLoop::runInLoop(const Functor& f)
{
    f();
}
