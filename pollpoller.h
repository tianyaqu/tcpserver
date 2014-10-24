#include <vector>
#include <map>
#include <poller.h>

class Channel;
class Poller
{
public:
    typedef std::vector<Channel*> ChannelList;
    Poller();
    ~Poller();
    void poll(ChannelList* list);
    //when a channel get a new fd,it'll come here
    void updateChannel(Channel* c);
    void removeChannel(Channel* c);
private:
    std::vector<struct pollfd> fdSet_;
    std::map<int,Channel*> channelMap_;
};
