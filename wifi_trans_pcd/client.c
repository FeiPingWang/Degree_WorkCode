#include <stdio.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <string.h>  
#include <errno.h>  
#include <netinet/in.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <arpa/inet.h>  
#include <sys/select.h>  
#include <pthread.h>

#define MAXLINE 1024  
#define SERV_PORT 6000  
#define MAXPTHREAD 500

int curConnect = 0;

//建立连接（线程调用）
int creatConnect(char* ipServer)
{
	int connfd;
	char *buf = "hello";
	struct sockaddr_in servaddr; 
	
	printf("pthread ID created: %d\n",pthread_self());
	
	if((connfd = socket(AF_INET,SOCK_STREAM, 0)) == -1 )  
    {  
        printf("Socket Error...\n" , errno );  
        exit( EXIT_FAILURE );  
    }  
    //套接字信息  
    bzero(&servaddr, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(SERV_PORT);  
    inet_pton(AF_INET, ipServer, &servaddr.sin_addr);  
      
    //链接server  
    if(connect(connfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)  
    {  
        printf("Connect error..\n");  
        exit(EXIT_FAILURE);  
    }
	write(connfd,buf,sizeof(buf));
	printf("connect %d",curConnect++);
	while(1)
	{
		
	}
	printf("pthread ID exit : %d\n",pthread_self());
	pthread_exit(0);

}

int main(int argc, char **argv)  
{  
    char  buf[MAXLINE];  
	pthread_t pthId;
	int i = 0;
	int err = 0;
    if(argc != 2)  
    {  
        printf("Input server ip !\n");  
        exit( EXIT_FAILURE );  
    }  
    //建立套接字  
    for(i = 0;i<MAXPTHREAD;i++)
	{
		err = pthread_create(&pthId,NULL,creatConnect,argv[1]);
		if(err != 0)
		{
			printf("create error: %d",errno);
			exit(EXIT_FAILURE);
		}
	//	sleep(1);
	}
	pthread_join(pthId,NULL);
	printf("create ok\n");
    return 0;  
}  

