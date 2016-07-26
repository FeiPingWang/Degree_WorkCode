#ifndef __CLIENT_H
#define __CLIENT_H

#include "common.h"

/***********函数声明************/
void* transFile(void* arg);
int waitFileReady(int fd);

/***********声明结束***********/

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
	if(fd == NULL)  
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

//等待并判断子进程的管道消息
int waitFileReady(int fd)
{
	int nread = 0;
	int result;
	int res = 0;
	char buf[1024];
	nread = read(fd,buf,1024);	//阻塞读
	printf("recvive %s\n",buf);
	if(nread == -1)
	{
		printf("read error\n");
		result = -1;
	}
	if(nread == 0)
		result = 2;
	else
	{
		if((res = strcmp("FILE_READY",buf)) == 0)
			result = 1;
		if((res = strcmp("ALLDONE",buf)) == 0)
			result = 2;
	}
	return result;
	
}

#endif	