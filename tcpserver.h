#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

class EventLoop;
class Acceptor;
class TcpServer
{
    public:
        TcpServer(EventLoop* loop,bool loopbackOnly,unsigned short port);
        ~TcpServer();
        void start();
        void OnConnection(int fd,const struct sockaddr_in& addr);
    private:
        void onConnection(); 
        EventLoop *loop_;
        Acceptor* acceptor_;
};
