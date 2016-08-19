#include <iostream>
#include "client.h"
#include <muduo/net/EventLoopThread.h>

using namespace std;
using namespace muduo;
using namespace muduo::net;

int main(int argc, char *argv[])
{
    LOG_INFO << "pid = " << getpid();
	if(argc < 3)
	{
		LOG_INFO << "missing ip or port";
		exit(0);
	}
	EventLoopThread loopThread;		//在别的线程中连接，主线程为空
	
	uint16_t port = static_cast<uint16_t>(atoi(argv[2]));
	InetAddress clientAddr(argv[1],port);
	
	WfpClient client(loopThread.startLoop(),clientAddr);
	client.connect();
}
	