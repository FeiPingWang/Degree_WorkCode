#include "client.h"

int main(int argc, char **argv)  
{  
	int connfd;
	struct sockaddr_in servaddr; 
	pid_t forkPid;
	int pipeFd[2];	//pipe描述符
	int resultPipe = 0;
    if(argc != 3)  
    {  
        printf("Input server ip and filename!\n");  
        exit( EXIT_FAILURE );  
    } 
	
	if((resultPipe = pipe(pipeFd)) == -1)
	{
		printf("pipe error\n");
		exit(EXIT_FAILURE);
	}
	//创建2个进程
	forkPid = fork();
	
	if(forkPid == -1)
	{
		printf("fork error\n");
		exit(EXIT_FAILURE);
	}
	
	if(forkPid == 0)	//子进程
	{
		//此处调用处理pcd文件的程序
		//处理完成后，通过进程通信发送到主进程，主进程开始发送文件到服务器
		//printf("FILE_READY\n ");
		char *buf = "FILE_READY";
		char *buff = "ALL_DONE";
		close(pipeFd[0]);	//关闭读
		write(pipeFd[1],buf,strlen(buf)+1);
		sleep(5);
		//write(pipeFd[1],buff,strlen(buff)+1);
		
	}
	//父进程
	close(pipeFd[1]);
	while(1)
	{
		char *resultType;
		int result;
		result = waitFileReady(pipeFd[0]);
		
		if(result == 1)
			printf("start\n");
		else if(result == 2)
			break;
		else if(result == -1)
			break;
		
		//父进程
		if((connfd = socket(AF_INET,SOCK_STREAM, 0)) == -1 )  
		{  
			printf("Socket Error...\n",errno);  
			exit( EXIT_FAILURE );  
		}  
		//套接字信息  
		bzero(&servaddr, sizeof(servaddr));  
		servaddr.sin_family = AF_INET;  
		servaddr.sin_port = htons(PORT);  
		inet_pton(AF_INET, argv[1], &servaddr.sin_addr);  
		  
		//连接server  
		if(connect(connfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)  
		{  
			printf("Connect error..\n");  
			exit(EXIT_FAILURE);  
		}	
		struct parameter *myarg;
		myarg = (struct parameter*)malloc(sizeof(struct parameter));
		
		myarg->fd = connfd;
		strcpy(myarg->filename,argv[2]);
		
		pthread_t threadPid;
		pthread_create(&threadPid,NULL,transFile,myarg);
		
		pthread_join(threadPid,NULL);
		sleep(1);
		close(connfd);
	}
	printf("create ok\n");
    return 0;  
}  
