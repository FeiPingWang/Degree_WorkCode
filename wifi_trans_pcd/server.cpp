#include "common.h"
#include <map>
#include "./thread_poll.h"	//线程池模型
using namespace std;

int  listen_fd;  
int  conn_fd;  
int  epoll_fd;  
char buf[MAXLINE];  
socklen_t Socklen = sizeof( struct sockaddr_in);

struct  epoll_event ev;  
struct  epoll_event evs[MAXEPOLL];  //返回就绪的描述符数组
struct sockaddr_in servaddr;  
struct sockaddr_in cliaddr;  

map<int,time_t> sock_mp;
pthread_mutex_t time_lock = PTHREAD_MUTEX_INITIALIZER;

/*设置描述符为非阻塞*/
int setnonblocking(int fd)  
{  
	int flags;
	flags = fcntl( fd, F_GETFD, 0 );
	flags |= O_NONBLOCK;
    if( fcntl( fd, F_SETFL,flags) == -1 )  
    {  
        printf("Set blocking error : %d\n", errno);  
        return -1;  
    }  
    return 0;  
}  

/*处理有数据可读的任务*/
void* handler_readable(void* arg)
{
	FILE *fp;
	char readBuf[BUFFSIZE];
	int nread,nwrite;
	int connfd = *((int*)arg);
		
	while(1)
	{
		nread = recv(connfd,readBuf,BUFFSIZE,0);
		printf("nread is %d\n",nread);
		if(nread == -1)
		{
			if(errno == EAGAIN || errno == EWOULDBLOCK)	//EOF
			{
				printf("recv finish,exit...\n");
				fclose(fp);
				break;
			}
			else if(errno == EPIPE)	//（待定）
			{
				printf("keepalive\n");
				break;
			}
			else{
				printf("something is error\n");
				exit(EXIT_FAILURE);
			}
		}
		else if(nread == 0)		//客户端关闭
		{
			epoll_ctl(epoll_fd, EPOLL_CTL_DEL, connfd, &ev);
			printf("client close\n");
			close(connfd);
			fclose(fp);
			break;
		}
		else{
			printf("start recv file\n");
			fp = fopen("test.txt","wb+");		//二进制读写，可以传输任何文件
			nwrite = fwrite(readBuf,sizeof(char),nread,fp);
			//printf("%s\n",readBuf);
			if(nwrite < nread)  
			{  
				printf("fwrite error: %d\n",errno);
				exit(1);  
			}  
			bzero(readBuf,BUFFSIZE);  
		}
			
	}
}

/*设置套接字的keepalive选项*/
int setKeepAlive(int connfd)
{
	int keepalive = 1;
	int keepidle = 10;		//间隔时间
	int keepinterval = 2;	//发送探测报文的间隔
	int keepcount = 5;		//发送的次数
	int sock_op = 1;
	if(setsockopt(connfd,SOL_SOCKET,SO_KEEPALIVE,&keepalive,sizeof(keepalive)) == -1)
	{
		perror("setsockopt error\n");
		close(connfd);
		exit(EXIT_FAILURE);
	}
	//设置新的值
	int len = sizeof(keepinterval);	
	setsockopt(connfd,SOL_TCP,TCP_KEEPIDLE,&keepidle,len);
	setsockopt(connfd,SOL_TCP,TCP_KEEPINTVL,&keepinterval,len);
	setsockopt(connfd,SOL_TCP,TCP_KEEPCNT,&keepcount,len);
#ifdef DEBUG
	printf("set keepalive ok\n");
#endif
}

//长连接心跳监听线程函数(待完成)
void* connect_timeout(void* arg)
{
	printf("connect_timeout\n");
	time_t nowtime;
	printf("map size %d\n",sock_mp.size());
	while(1)
	{
		pthread_mutex_lock(&time_lock);
		for(auto begin = sock_mp.begin();begin != sock_mp.end();begin++)
		{
			time(&nowtime);
			printf("%d\n",nowtime);
			int fd = begin->first;
			printf("fd is  %d\n",fd);
			if(nowtime - sock_mp[fd] > 5)
			{
				printf("connet %d timeout\n",fd);
				epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &ev);
				close(fd);	//关闭该连接
				sock_mp.erase(begin);
			}
		}
		pthread_mutex_unlock(&time_lock);
		sleep(10);
	}	
}

//处理新的客户连接任务
void* handler_new_connect(void* arg)
{
	if((conn_fd = accept(listen_fd,(struct sockaddr*)&cliaddr, &Socklen)) == -1)  
    {  
        printf("Accept Error: %d\n", errno);  
        exit(EXIT_FAILURE);  
    }     
    printf( "client %s is connecting...\n",inet_ntoa((cliaddr.sin_addr)));
	
	setnonblocking(conn_fd);
    //setKeepAlive(conn_fd);	//设置keepalive选项
	
    ev.events = EPOLLIN | EPOLLET | EPOLLHUP;
    ev.data.fd = conn_fd;       
				
    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_fd, &ev) < 0 )  
    {  
        printf("Epoll Error : %d\n", errno);  
        exit(EXIT_FAILURE);  
    }   
				
	pthread_mutex_lock(&time_lock);//获取时间
	time_t newtime;
	time(&newtime);
	sock_mp[conn_fd] = newtime;
	printf("time is %d\n",newtime);
	pthread_mutex_unlock(&time_lock);
}

int main(void)
{
    int    wait_fds;    //epoll_wait 的返回值  
    int    i = 0;  
	int sock_op = 1;

	if((listen_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		printf("socket error :d\n",errno);
		exit(EXIT_FAILURE);
	}
	
	bzero(&servaddr, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  
    servaddr.sin_port = htons(PORT);  

	//设置套接字选项 SO_REUSEADDR
	setsockopt(listen_fd,SOL_SOCKET,SO_REUSEADDR,&sock_op,sizeof(sock_op));
	
	//监听套接字设为非阻塞
	if(setnonblocking(listen_fd) == -1)
	{  
        printf("Setnonblocking Error : %d\n", errno);  
        exit( EXIT_FAILURE );  
    }  
	if(bind(listen_fd, (struct sockaddr *)&servaddr, sizeof( struct sockaddr )) == -1 )
	{  
        printf("Bind Error : %d\n", errno);  
        exit( EXIT_FAILURE );  
    } 
	if(listen( listen_fd, MAXBACK ) == -1 )
	{  
        printf("Listen Error : %d\n", errno);  
        exit( EXIT_FAILURE );  
    }  
	
    //以下是处理部分，使用epoll
	epoll_fd = epoll_create(MAXEPOLL);
	ev.data.fd = listen_fd;                 //监听套接字加入  
    ev.events = EPOLLIN | EPOLLET;

    if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,listen_fd,&ev) < 0){  
        printf("Epoll Error : %d\n", errno);  
        exit( EXIT_FAILURE );  
    } 
	
	//开启线程池，创建5个线程
	poll_init(5);	
	pthread_t timeoutId;
	//pthread_create(&timeoutId,NULL,connect_timeout,NULL);	//开启检测
	
	while(1)
	{
		if((wait_fds = epoll_wait(epoll_fd,evs,MAXEPOLL, -1 )) == -1)
		{  
            printf("Epoll Wait Error : %d\n", errno);  
            exit( EXIT_FAILURE );  
        }  
		for(i = 0;i < wait_fds;i++)
		{
			if(evs[i].data.fd == listen_fd)      //有新的客户连接                      
            {  
                poll_add_worker(handler_new_connect,NULL);      
            }
			else			
			{		
				if(evs[i].events & EPOLLIN)	//对应的文件描述符可以读（包括对端SOCKET正常关闭）
				{
					//handler_readable(&evs[i].data.fd);
					poll_add_worker(handler_readable,&evs[i].data.fd);
				}
				if(evs[i].events & EPOLLHUP)	//连接关闭
					printf("客户端连接崩溃\n");
				if(evs[i].events & EPOLLOUT)	//可写
				{
					//poll_add_worker(handler_writeable,&evs[i].data.fd);
				}
			}
		}
	}
	close(listen_fd);
	free(evs);
	return 0;
}



