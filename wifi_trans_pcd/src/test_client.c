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

static const int MAXPTHREAD = 200;
static const int BUFFSIZE = 4096;
static const int SERV_PORT = 6000;
static const int MAXLINE = 1024;

int creatConnect(char* ipServer)
{
	int connfd;
	char *buf = "Hello server!";
	char recvBuf[BUFFSIZE];
	struct sockaddr_in servaddr; 
	int nwrite = 0;
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
	
	nwrite = send(connfd,buf,strlen(buf),0);	//发送一个问候语
	printf("waiting reply\n");
	//recv(connfd,recvBuf,nwrite,0);
	//printf("service says %s\n",recvBuf);
	
    //printf("Transfer file finished !\n");  
	sleep(60);	//线程休息60秒
	
	pthread_exit(0);
    //close(connfd);  
}

int main(int argc, char **argv)  
{  
    char  buf[MAXLINE];  
	pthread_t *pthId;
	int i = 0;
	int err = 0;
    if(argc != 2)  
    {  
        printf("Input server ip and filename!\n");  
        exit( EXIT_FAILURE );  
    }  
	//creatConnect(argv[1]);
    //建立套接字  
	pthId = (pthread_t*)malloc(sizeof(pthread_t)*MAXPTHREAD);	//分配线程id数组
	
    for(i = 0;i < MAXPTHREAD;i++)
	{
		err = pthread_create(&pthId[i],NULL,creatConnect,argv[1]);
		if(err != 0)
		{
			printf("create error: %d",errno);
			exit(EXIT_FAILURE);
		}
		//sleep(1);
	}
	for(i = 0;i<MAXPTHREAD;i++)
		pthread_join(pthId[i],NULL);
	printf("create ok\n");
    return 0;  
}  


