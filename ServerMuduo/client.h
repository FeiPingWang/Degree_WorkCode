#ifndef __CLIENT_H
#define __CLIENT_H

#include "codec.h"

#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoopThread.h>
#include <muduo/net/TcpClient.h>
#include <iostream>
#include <stdio.h>

using namespace muduo;
using namespace muduo::net;

class WfpClient : public boost::noncopyable{
public:
	WfpClient(EventLoop *loop,const InetAddress &clientAddr)
		: client_(loop,clientAddr,"client"),
		codec_(boost::bind(&WfpClient::onStringMessage, this, _1, _2, _3))
	{
		//构造函数里设置回调函数
		client_.setConnectionCallback(
            boost::bind(&WfpClient::onConnection, this, _1));
			
        client_.setMessageCallback(
            boost::bind(&LengthHeaderCodec::onMessage, &codec_, _1, _2, _3));
        client_.enableRetry();
			
	}
	
	void connect()
    {
        client_.connect();
    }

    void disconnect()
    {
        client_.disconnect();
    }
	
	void write(const StringPiece &message)
    {
        MutexLockGuard lock(mutex_);
        if (connection_)
        {
            codec_.send(get_pointer(connection_), message);
        }
    }
	
private:
	void onConnection(const TcpConnectionPtr &conn)
    {
        LOG_INFO << conn->localAddress().toIpPort() << " -> "
            << conn->peerAddress().toIpPort() << " is "
            << (conn->connected() ? "UP" : "DOWN");

        MutexLockGuard lock(mutex_);
        if (conn->connected())
        {
            connection_ = conn;
        } else
        {
            connection_.reset();
        }
    }
	void onStringMessage(const TcpConnectionPtr&,
                         const string &message,
                         Timestamp)
    {
        printf("<<< %s\n", message.c_str());
    }

	
private:
	TcpClient client_;
    LengthHeaderCodec codec_;
    MutexLock mutex_;
    TcpConnectionPtr connection_;
};



#endif