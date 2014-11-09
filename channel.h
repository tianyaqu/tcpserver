#include <boost/function.hpp>
#include <poll.h>

class EventLoop;
class Channel
{
public:
    typedef boost::function<void()> Callback;
    Channel(EventLoop* loop,int fd);
    //Channel(EventLoop* loop);
    ~Channel();
    void registerReadCallback(const Callback& r);
    void registerWriteCallback(const Callback& w);
    void handleEvent();
    void enableRead() { events_ |= (POLLIN|POLLPRI);update();}
    void enableWrite(){ events_ |= POLLOUT;update();}
    int getIndex(){ return index_; }
    void setIndex(unsigned int i){ index_ = i; }
    int getEvent() { return events_; }
    int getFd() { return fd_; }
    std::string getName(){ return name; };
    //void registerWriteCallback();
private:
    //when connectiton is established,notify the poller.
    void update();
    Callback readCallback_;
    Callback writeCallback_;
    int events_;
    int fd_;
    int index_;
    std::string name;
    EventLoop* loop_;
};
