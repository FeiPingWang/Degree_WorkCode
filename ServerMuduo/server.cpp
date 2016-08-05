#include "server.h"

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Mutex.h>
#include <boost/bind.hpp>
#include <stdio.h>

using namespace muduo;
using namespace muduo::net;

WfpServer::WfpServer(EventLoop* loop,const InetAddress& listenAddr)
	: server_(loop, listenAddr, "EchoServer"),
	  codec_(boost::bind(&WfpServer::onStringMessage,this,_1,_2,_3))		//构造codec_
{
	server_.setConnectionCallback( boost::bind(&WfpServer::onConnection, this, _1));
	server_.setMessageCallback( boost::bind(&LengthHeaderCodec::onMessage, &codec_, _1, _2, _3));
}

void WfpServer::start()
{
	server_.start();
}

//客户端连接和断开回调函数
void WfpServer::onConnection(const TcpConnectionPtr& conn)
{
	LOG_INFO << conn->peerAddress().toIpPort() << " -> "
			 << (conn->connected() ? "UP" : "DOWN");	//调用连接函数这里
	
	if(conn->connected())
	{
		connects_.insert(conn);
	}
	else
	{
		connects_.erase(conn);
	}
			 
}

//消息处理完成发送给所有客户 回调函数
void WfpServer::onStringMessage(const TcpConnectionPtr& conn,const string &message,Timestamp time)
{
	for(auto it = connects_.begin();it != connects_.end();it++)
	{
		codec_.send(get_pointer(*it),message);
	}
}

int main(int argc,char** argv)
{
	LOG_INFO << "pid= " <<getpid();
	if(argc > 1)
	{
		EventLoop loop;
		int16_t port = static_cast<int16_t>(atoi(argv[1]));
		InetAddress ServerAddr(port);
		WfpServer server(&loop,ServerAddr);
		
		server.start();
		loop.loop();
	}
	return 0;
}

