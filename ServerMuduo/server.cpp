#include "server.h"

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Mutex.h>
#include <boost/bind.hpp>
#include <stdio.h>

using namespace muduo;
using namespace muduo::net;

WfpServer::WfpServer(EventLoop* loop,const InetAddress& listenAddr)
	: server_(loop, listenAddr, "WfpServer")
{
	server_.setConnectionCallback( boost::bind(&WfpServer::onConnection, this, _1));
	server_.setMessageCallback( boost::bind(&WfpServer::onMessage, this, _1, _2, _3));
}

void WfpServer::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
	LOG_INFO << conn->localAddress().toIpPort() << " is "
			 << (conn->connected() ? "UP" : "DOWN");
}

//简单的回显函数
void WfpServer::onMessage(const muduo::net::TcpConnectionPtr& conn,
                           muduo::net::Buffer* buf,
                           muduo::Timestamp time)
{
	muduo::string msg(buf->retrieveAllAsString());
	LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
			 << "data received at " << time.toString();
	printf("<<< %s\n", msg.c_str());
	//conn->send(msg);
}

void WfpServer::start()
{
	server_.start();
}