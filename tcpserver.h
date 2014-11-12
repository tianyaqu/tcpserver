#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <map>
#include <string>

class EventLoop;
class Acceptor;
class TcpConnection;
class TcpServer
{
    public:
        TcpServer(EventLoop* loop,bool loopbackOnly,unsigned short port);
        ~TcpServer();
        void start();
        void OnConnection(int fd,const struct sockaddr_in& addr);
        EventLoop* currentLoop(){return loop_;}
    private:
        EventLoop* loop_;
        Acceptor* acceptor_;
        std::map<const std::string,TcpConnection*> connMap_;
        unsigned int connIndex_;
};
