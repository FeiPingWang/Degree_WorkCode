#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <string.h>  
#include <errno.h>  
#include <fcntl.h>
#include <pthread.h>
#include <time.h>

#include <sys/types.h>  
#include <sys/socket.h>  
#include <sys/select.h>  
#include <sys/epoll.h>
#include <sys/resource.h>

#include <netinet/tcp.h> 
#include <netinet/in.h>  
#include <arpa/inet.h> 

static const size_t MAXLINE = 1024; 
static const size_t PORT = 9877;  
static const size_t MAXPTHREAD = 500;
static const size_t BUFFSIZE = 4096;
static const size_t MAXEPOLL = 65535;
static const size_t MAXBACK = 1000;

//传递多个参数给线程
struct parameter
{
	int fd;
	char filename[20];
};
#endif