#include "client.h"
#include <boost/bind.hpp>

using namespace muduo;
using namespace muduo::net;

const int kBufSize = 64*1024;	//64k
const char* g_file = "Makefile";
	
void WfpClient::onConnection(const TcpConnectionPtr &conn)
{
    LOG_INFO << conn->peerAddress().toIpPort() << " is "
        << (conn->connected() ? "UP" : "DOWN");
    if (conn->connected())	//连接上
    {
        //connection_ = conn;
		LOG_INFO << "FileServer - Sending file " << g_file
             << " to " << conn->peerAddress().toIpPort();

		FILE* fp = ::fopen(g_file, "rb");
		if (fp)
		{
			conn->setContext(fp);
			char buf[kBufSize];
			size_t nread = ::fread(buf, 1, sizeof buf, fp);
			conn->send(buf, static_cast<int>(nread));
		}
		else
		{
			conn->shutdown();
			LOG_INFO << "FileServer - no such file";
		}
    } 	
	else	//断开连接
	{
		if (!conn->getContext().empty())
		{
			FILE* fp = boost::any_cast<FILE*>(conn->getContext());
			if (fp)
			{	
				::fclose(fp);
			}
		}
	}
}

/*发送完成回调函数*/
void WfpClient::onWriteComplete(const TcpConnectionPtr& conn)
{
	LOG_INFO << "47";
	FILE* fp = boost::any_cast<FILE*>(conn->getContext());	//得到之前保存的上下文
	char buf[kBufSize];
	size_t nread = ::fread(buf, 1, sizeof buf, fp);
	LOG_INFO << "trans "<< nread;
	if (nread > 0)
	{
		conn->send(buf, static_cast<int>(nread));
	}
	else
	{
		::fclose(fp);
		fp = NULL;
		conn->setContext(fp);
		conn->shutdown();
		LOG_INFO << "FileServer - done";
	}
}

void WfpClient::onMessage(const TcpConnectionPtr& conn,muduo::net::Buffer* buf,Timestamp time)
{
	LOG_INFO << "receive ";
}
