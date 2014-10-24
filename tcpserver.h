class EventLoop;
class Acceptor;
class TcpServer
{
    public:
        TcpServer(EventLoop* loop,bool loopbackOnly,unsigned short port);
        ~TcpServer();
        void start();
    private:
        void onConnection(); 
        EventLoop *loop_;
        Acceptor* acceptor_;
};
