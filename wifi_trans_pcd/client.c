#include "common.h"

//建立连接（线程调用）
void* transFile(void* arg)
{
	char buf[BUFFSIZE];
	struct parameter *myarg;
	myarg = (struct parameter*)malloc(sizeof(struct parameter));
	myarg = (struct parameter*)arg;
	
	char filename[20];
	strcpy(filename,myarg->filename);
	int connfd = myarg->fd;
	
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
	pthread_exit(0);
}

int main(int argc, char **argv)  
{  
   // char  buf[MAXLINE];  
	int connfd;
	struct sockaddr_in servaddr; 
	
    if(argc != 3)  
    {  
        printf("Input server ip and filename!\n");  
        exit( EXIT_FAILURE );  
    } 
	
	if((connfd = socket(AF_INET,SOCK_STREAM, 0)) == -1 )  
    {  
        printf("Socket Error...\n" , errno );  
        exit( EXIT_FAILURE );  
    }  
    //套接字信息  
    bzero(&servaddr, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(PORT);  
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);  
      
    //链接server  
    if(connect(connfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)  
    {  
        printf("Connect error..\n");  
        exit(EXIT_FAILURE);  
    }	
	struct parameter *myarg;
	myarg = (struct parameter*)malloc(sizeof(struct parameter));
	
	myarg->fd = connfd;
	strcpy(myarg->filename,argv[2]);
	
	pthread_t pid;
	
	pthread_create(&pid,NULL,transFile,myarg);
	
	pthread_join(pid,NULL);
	sleep(1);
	close(connfd);
	printf("create ok\n");
    return 0;  
}  
