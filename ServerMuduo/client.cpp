#include "client.h"

using namespace muduo;
using namespace muduo::net;

int main(int argc, char *argv[])
{
    LOG_INFO << "pid = " << getpid();
    if (argc > 2)
    {
        EventLoopThread loopThread;
        uint16_t port = static_cast<uint16_t>(atoi(argv[2]));
        InetAddress serverAddr(argv[1], port);

        WfpClient client(loopThread.startLoop(), serverAddr);
        client.connect();
        std::string line;
        while (std::getline(std::cin, line))
        {
            client.write(line);
        }
        client.disconnect();
        CurrentThread::sleepUsec(1000 * 1000);  // wait for disconnect, see ace/logging/client.cc
    } else
    {
        printf("Usage: %s host_ip port\n", argv[0]);
    }
}