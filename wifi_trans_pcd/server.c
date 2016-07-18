#include <stdio.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/types.h>  
#include <errno.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/epoll.h>            
#include <fcntl.h>                    
#include <sys/resource.h>
#include <pthread.h>
#include <time.h>

#include "./thread_poll.h"	//线程池模型

//#define DEBUG

static const int  MAXEPOLL = 200000;
static const int PORT = 6000;
static const int MAXBACK = 1000;
static const int MAXLINE = 1024;
static const int BUFFSIZE = 4096;
static int num = 0;
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

/*接收客户端发来的文件，使用TCP协议*/
void* recvFile(void* arg)
{
		FILE *fp;
		char *fileTime = NULL;
		fp = fopen("713.png","ab");		//二进制读写，可以传输任何文件
		char buf[BUFFSIZE];
		int nread,nwrite;
		int connfd = *((int*)arg);
		//printf("connfd %d\n",connfd);

		while(nread = recv(connfd,buf,BUFFSIZE,0))
		{
			if(nread == -1)
			{
				printf("recv end: %d\n",errno);
				exit(EXIT_FAILURE);
			}
			nwrite = fwrite(buf,sizeof(char),nread,fp);
			printf("nread is %d\n",nread);	
			if(nwrite < nread)  
			{  
				printf("fwrite error: %d\n",errno);
				exit(1);  
			}  
			bzero(buf,BUFFSIZE);  
		}
		fclose(fp);
		pthread_exit(0);
		//close(connfd);
}

void* testConnect(void* arg)
{
	int nread = 0;
	char buf[BUFFSIZE];
	int connfd = *((int*)(arg));
	nread = recv(connfd,buf,BUFFSIZE,0);
	printf("receive %s %d\n",buf,num++);
	
	//send(connfd,buf,nread,0);
	//printf("reply to client\n");
}


int main(void)
{
	int    listen_fd;  
    int    conn_fd;  
    int    epoll_fd;  
    int    nread;  
    int    cur_fds = 0;               //当前已经存在的数量  
    int    wait_fds;               //epoll_wait 的返回值  
    int    i;  
	//pthread_t pthId;
	
    struct sockaddr_in servaddr;  
    struct sockaddr_in cliaddr;  
    struct  epoll_event ev;  
    struct  epoll_event evs[MAXEPOLL];  //返回就绪的描述符数组
    struct  rlimit  rlt;        		//设置连接数所需  
    char    buf[MAXLINE];  
    socklen_t Socklen = sizeof( struct sockaddr_in);
	
	rlt.rlim_max = rlt.rlim_cur = MAXEPOLL;  //更改最大连接数量(无限制)
	
	if(setrlimit(RLIMIT_NOFILE,&rlt) == -1)  //更改限制（软，硬）  
    {  
        printf("Setrlimit Error : %d\n", errno);  
        exit( EXIT_FAILURE );  
    }  

	bzero(&servaddr, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  
    servaddr.sin_port = htons(PORT);  

	if((listen_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		printf("socket error :d\n",errno);
		exit(EXIT_FAILURE);
	}
	//监听套接字设为非阻塞
	if(setnonblocking(listen_fd) == -1 )  
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
	
	/*开启线程池，创建5个线程*/
	poll_init(10);
	
    //以下是处理部分，使用epoll
	epoll_fd = epoll_create(MAXEPOLL);		//创建
   // ev.events = EPOLLIN | EPOLLET;      	//边沿触发，检测读（只报告一次） 
	ev.events = EPOLLIN;      				//边沿触发，检测读(会一直报告，不容易出错)
    ev.data.fd = listen_fd;                 //监听套接字加入  
    if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,listen_fd,&ev) < 0)  
    {  
        printf("Epoll Error : %d\n", errno);  
        exit( EXIT_FAILURE );  
    }  
	/*无限循环*/
	while(1)
	{
		if((wait_fds = epoll_wait(epoll_fd,evs,MAXEPOLL, -1 )) == -1)  
        {  
            printf( "Epoll Wait Error : %d\n", errno );  
            exit( EXIT_FAILURE );  
        }  
		for(i = 0;i < wait_fds;i++)
		{
			if(evs[i].data.fd == listen_fd)      //有新的客户连接                      
            {  
                if((conn_fd = accept(listen_fd,(struct sockaddr*)&cliaddr, &Socklen)) == -1)  
                {  
                    printf("Accept Error : %d\n", errno);  
                    exit( EXIT_FAILURE );  
                }  
                //打印客户的IP
                printf( "Server get from client %d\n",cur_fds++);  
                
				//把新连接加入epoll中
                ev.events = EPOLLIN | EPOLLET;      	  
                ev.data.fd = conn_fd;                    
                if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_fd, &ev) < 0 )  
                {  
                    printf("Epoll Error : %d\n", errno);  
                    exit( EXIT_FAILURE );  
                }   
                continue;         
            }
			else							   //有数据需要读
			{
				pthread_t pthId;
				
				//printf("%d\n",evs[i].data.fd);
				/*if(pthread_create(&pthId,NULL,recvFile,&evs[i].data.fd))
				{
					printf("pthread_create error\n");
					exit(EXIT_FAILURE);
				}*/
#ifndef DEBUG	//如果没有定义调试
				printf("处理文件开始\n");
				//poll_add_worker(recvFile,&evs[i].data.fd);
				poll_add_worker(testConnect,&evs[i].data.fd);
				printf("thread handle finish\n");
#else
				testConnect(&evs[i].data.fd);
#endif
			}
		}
	}
	close(listen_fd);
	close(epoll_fd);
	return 0;
}



