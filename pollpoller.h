#include <vector>
#include <map>
#include <poll.h>

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
    //std::vector<struct pollfd> fdSet_;
    typedef std::vector<struct pollfd> PollFdList;
    PollFdList fdSet_;
  typedef std::map<int, Channel*> ChannelMap;
    std::map<int,Channel*> channelMap_;
    void fillActiveChannels(ChannelList*) const;
};
