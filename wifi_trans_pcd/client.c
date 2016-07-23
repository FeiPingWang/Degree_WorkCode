#include "common.h"

//建立连接（线程调用）
int creatConnect(char* ipServer,char* filename)
{
	int connfd;
	char buf[BUFFSIZE];
	struct sockaddr_in servaddr; 
	
	if((connfd = socket(AF_INET,SOCK_STREAM, 0)) == -1 )  
    {  
        printf("Socket Error...\n" , errno );  
        exit( EXIT_FAILURE );  
    }  
    //套接字信息  
    bzero(&servaddr, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(PORT);  
    inet_pton(AF_INET, ipServer, &servaddr.sin_addr);  
      
    //链接server  
    if(connect(connfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)  
    {  
        printf("Connect error..\n");  
        exit(EXIT_FAILURE);  
    }
	//发送文件
	FILE *fd = fopen(filename,"rb+");
	if(fd==NULL)  
    {  
        printf("File :%s not found!\n",filename);  
		exit(EXIT_FAILURE);
    }  
	bzero(buf,BUFFSIZE);  
    int file_block_length=0;  
	
    while((file_block_length = fread(buf,sizeof(char),BUFFSIZE,fd))>0)  
    {  
        printf("file_block_length:%d\n",file_block_length); 
        if(send(connfd,buf,file_block_length,0)<0)  
        {  
            perror("Send");  
            exit(1);  
        }  
        bzero(buf,BUFFSIZE);     
    }  
    fclose(fd);  
    printf("Transfer file finished !\n");   
    close(connfd);  
	
}

int main(int argc, char **argv)  
{  
    char  buf[MAXLINE];  
	pthread_t pthId;
	int i = 0;
	int err = 0;
    if(argc != 3)  
    {  
        printf("Input server ip and filename!\n");  
        exit( EXIT_FAILURE );  
    }  
	creatConnect(argv[1],argv[2]);
   
	printf("create ok\n");
    return 0;  
}  
