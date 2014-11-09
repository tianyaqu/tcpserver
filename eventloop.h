#include <vector>

class Channel;
class Poller;
class EventLoop
{
public:
    typedef std::vector<Channel*> ChannelList;
    EventLoop();
    ~EventLoop();
    void loop();
    void updateChannel(Channel* c);
private:
    ChannelList active_;
    Poller* poller_;
    bool quit_;
};
