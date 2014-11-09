#include <netinet/in.h>
#include <netinet/tcp.h>
#include <boost/function.hpp>

class Channel;
class EventLoop;
class Acceptor
{
public:
    typedef boost::function<void(int fd,const struct sockaddr_in& addr)> NewConnCallback;
    Acceptor(EventLoop* loop,bool loopbackOnly,unsigned short port);
    ~Acceptor();
    void listen();
    void setNewConnCallback(const NewConnCallback& cb);
private:
    void onRead();
    Channel* acceptChannel_;
    int listenFd_;
    NewConnCallback newConnCallback_;
};
