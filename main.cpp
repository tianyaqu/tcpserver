#include "tcpserver.h"
#include "eventloop.h"

int main()
{
    EventLoop loop;
    TcpServer s(&loop,true,8001);
    s.start();
    loop.loop();
}
