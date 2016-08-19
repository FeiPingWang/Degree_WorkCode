#ifndef __CLIENT_H
#define __CLIENT_H

#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/TcpClient.h>

#include <iostream>
#include <stdio.h>

using namespace muduo;
using namespace muduo::net;

class WfpClient : public boost::noncopyable{
public:
	WfpClient(EventLoop *loop,const InetAddress &clientAddr)
		: client_(loop,clientAddr,"client")
	{
		//构造函数里设置回调函数
		client_.setConnectionCallback(boost::bind(&WfpClient::onConnection, this, _1));
			
        client_.setMessageCallback(boost::bind(&WfpClient::onMessage, this, _1, _2, _3));
		
		client_.setWriteCompleteCallback(boost::bind(&WfpClient::onWriteComplete, this, _1));
		
        client_.enableRetry();	//重新连接
	}

	void connect()
    {
        client_.connect();
    }
	
private:
	void onConnection(const TcpConnectionPtr &conn);
	void onMessage(const TcpConnectionPtr& conn,muduo::net::Buffer* buf,Timestamp time);
	void onWriteComplete(const TcpConnectionPtr& conn);
	void onHighWaterMark(const TcpConnectionPtr& conn, size_t len)
	{
		LOG_INFO << "HighWaterMark " << len;
	}
private:
	TcpClient client_;
    TcpConnectionPtr connection_;
	MutexLock mutex_;
};



#endif