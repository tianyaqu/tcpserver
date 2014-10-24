#include "tcpserver.h"
#include "eventloop.h"

int main()
{
    EventLoop loop;
    TcpServer s(&loop,true,2345);
    s.start();
    loop.loop();
}
