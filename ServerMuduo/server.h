#ifndef __SERVER_H
#define __SERVER_H

#include <muduo/net/TcpServer.h>
#include <set>
#include <string>
#include "codec.h"

class WfpServer
{
public:
	WfpServer(muduo::net::EventLoop* loop,
             const muduo::net::InetAddress& listenAddr);
	void start();  	

private:
	void onConnection(const muduo::net::TcpConnectionPtr& conn);
	void onStringMessage(const muduo::net::TcpConnectionPtr& conn,const muduo::string &message,muduo::Timestamp time);

private:
	typedef std::set<muduo::net::TcpConnectionPtr> ConnectionList;	//存储连接的容器
	muduo::net::TcpServer server_;
	LengthHeaderCodec codec_;
	ConnectionList connects_;
};

#endif 
