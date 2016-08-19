#include <iostream>
#include "server.h"
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
using namespace std;
using namespace muduo;
using namespace muduo::net;

int main(int argc, char *argv[])
{
    LOG_INFO << "pid = " << getpid();
	if(argc < 2)
	{
		LOG_INFO << "missing port";
		exit(0);
	}
	EventLoop loop;
	uint16_t port = static_cast<uint16_t>(atoi(argv[1]));
	InetAddress serverAddr(port);
	WfpServer server(&loop,serverAddr);
	server.start();
	loop.loop();
	
	
}

