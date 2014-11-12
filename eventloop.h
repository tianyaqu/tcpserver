#include <vector>
#include <boost/function.hpp>

class Channel;
class Poller;
class EventLoop
{
public:
    typedef std::vector<Channel*> ChannelList;
    typedef boost::function<void()> Functor;
    EventLoop();
    ~EventLoop();
    void loop();
    void updateChannel(Channel* c);
    //interface for multi threads
    void runInLoop(const Functor& f);
private:
    ChannelList active_;
    Poller* poller_;
    bool quit_;
};
