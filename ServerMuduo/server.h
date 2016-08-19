/************* 接收服务器程序 *****************
************** by 王飞平 CAD415 ****************/

#ifndef __SERVER_H
#define __SERVER_H

#include <muduo/net/TcpServer.h>
#include <set>
#include <string>

class WfpServer
{
public:
	WfpServer(muduo::net::EventLoop* loop,
             const muduo::net::InetAddress& listenAddr);
	void start();  	

private:
	//处理连接的建立与关闭
	void onConnection(const muduo::net::TcpConnectionPtr& conn);
	//收到消息
	void onMessage(const muduo::net::TcpConnectionPtr& conn,muduo::net::Buffer* buf,muduo::Timestamp time);
	//void onWriteComplete(const muduo::net::TcpConnectionPtr& conn);
	
private:
	muduo::net::TcpServer server_;
	muduo::net::EventLoop* loop_;
};

#endif 
