#include "server.h"

#include <muduo/base/Logging.h>
#include <boost/bind.hpp>

using namespace muduo;
using namespace muduo::net;



WfpServer::WfpServer(EventLoop* loop,const InetAddress& listenAddr)
	: server_(loop, listenAddr, "EchoServer")
{
	server_.setConnectionCallback( boost::bind(&WfpServer::onConnection, this, _1));
	server_.setMessageCallback( boost::bind(&WfpServer::onMessage, this, _1, _2, _3));
}

void WfpServer::start()
{
	server_.start();
}

void WfpServer::onConnection(const TcpConnectionPtr& conn)
{
	LOG_INFO << "WfpServer - " << conn->peerAddress().toIpPort() << " -> "
			 << conn->localAddress().toIpPort() << " is "
			 << (conn->connected() ? "UP" : "DOWN");	//调用连接函数这里
			 
}

void WfpServer::onMessage(const TcpConnectionPtr& conn,Buffer* buf,Timestamp time)
{
	muduo::string msg(buf->retrieveAllAsString());
	LOG_INFO << conn->name() << " wfp " << msg.size() << " bytes, "
			 << "data received at " << time.toString();
	conn->send(msg);
}

