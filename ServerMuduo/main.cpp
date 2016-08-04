#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <boost/shared_ptr.hpp>

#include <stdio.h>

using namespace muduo;
using namespace muduo::net;

void onHighWaterMark(const TcpConnectionPtr &conn, size_t len)
{
    LOG_INFO << "HighWaterMark " << len;
}

void closefun(const TcpConnectionPtr & conn)
{
	LOG_INFO << "closefun test";
}

void connectFun(const TcpConnectionPtr & conn)
{
	LOG_INFO << "read 0 test";
}

const int kBufSize = 64 * 1024;
const char *g_file = NULL;
typedef boost::shared_ptr<FILE> FilePtr;

void onConnection(const TcpConnectionPtr &conn)
{
    LOG_INFO << "FileServer - " << conn->peerAddress().toIpPort() << " -> "
        << conn->localAddress().toIpPort() << " is "
        << (conn->connected() ? "UP" : "DOWN");
    if (conn->connected())
    {
        LOG_INFO << "FileServer - Sending file " << g_file
            << " to " << conn->peerAddress().toIpPort();
        conn->setHighWaterMarkCallback(onHighWaterMark, 5);
		
		conn->setCloseCallback(closefun);	//test closefun
		
		conn->setConnectionCallback(connectFun);	//read 0 时调用
		
        FILE *fp = ::fopen(g_file, "rb");
        if (fp)
        {
            FilePtr ctx(fp, ::fclose);
            conn->setContext(ctx);
            char buf[kBufSize];
            size_t nread = ::fread(buf, 1, sizeof buf, fp);
            conn->send(buf, static_cast<int>(nread));
        } else
        {
            conn->shutdown();
            LOG_INFO << "FileServer - no such file";
        }
    }//fp离开作用域会被释放
}

void onWriteComplete(const TcpConnectionPtr &conn)
{
    const FilePtr &fp = boost::any_cast<const FilePtr&>(conn->getContext());	//重新得到fp
    char buf[kBufSize];
    size_t nread = ::fread(buf, 1, sizeof buf, get_pointer(fp));//得到指针，调用fp.get()。
    if (nread > 0)
    {
        conn->send(buf, static_cast<int>(nread));
    } else
    {
        conn->shutdown();
        LOG_INFO << "FileServer - done";
    }
}

int main(int argc, char *argv[])
{
    LOG_INFO << "pid = " << getpid();
    if (argc > 1)
    {
        g_file = argv[1];

        EventLoop loop;
        InetAddress listenAddr(2021);
        TcpServer server(&loop, listenAddr, "FileServer");
        server.setConnectionCallback(onConnection);
        server.setWriteCompleteCallback(onWriteComplete);
        server.start();
        loop.loop();
    } else
    {
        fprintf(stderr, "Usage: %s file_for_downloading\n", argv[0]);
    }
}

