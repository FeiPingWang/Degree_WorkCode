#include "server.h"

int main(void)
{
    int    wait_fds;    //epoll_wait 的返回值  
    int    i = 0;  
	int    sock_op = 1;

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
					poll_add_worker(handler_readable,&evs[i].data.fd);
				}
				if(evs[i].events & EPOLLHUP)	//连接关闭
					printf("客户端连接崩溃\n");
				/*if(evs[i].events & EPOLLOUT)	//可写
				{
					//poll_add_worker(handler_writeable,&evs[i].data.fd);
				}*/
			}
		}
	}
	close(listen_fd);
	free(evs);
	return 0;
}



