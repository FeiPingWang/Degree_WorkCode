#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <boost/shared_ptr.hpp>
#include <iostream>

using namespace std;
using namespace muduo;
using namespace muduo::net;

int main(int argc, char *argv[])
{
    LOG_INFO << "pid = " << getpid();
	
}

