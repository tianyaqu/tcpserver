#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <string>
#include <boost/function.hpp>

class Channel;
class EventLoop;

class TcpConnection
{
public:
    TcpConnection(EventLoop* loop,int fd,const struct sockaddr_in& self,const struct sockaddr_in& peer);
    ~TcpConnection();
    void connEstablished();
    void connClosed();
private:
    typedef boost::function<void()> Callback;
    enum StateE { kDisconnected, kConnecting, kConnected, kDisconnecting };
    EventLoop* loop_;
    Channel* channel_; 
    std::string name_;
    int sockFd_;
    struct sockaddr_in self_;
    struct sockaddr_in peer_;
    StateE state_;
    void handleRead();
    void handleWrite();
    void handleClose();
    void setState(StateE s){state_ = s;}
};
