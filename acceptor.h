class Channel;
class EventLoop;
class Acceptor
{
public:
    Acceptor(EventLoop* loop,bool loopbackOnly,unsigned short port);
    void listen();
private:
    void onRead();
    Channel* acceptChannel_;
};
