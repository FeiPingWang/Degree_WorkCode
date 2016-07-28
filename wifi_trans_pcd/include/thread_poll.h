/*线程池实现*/

#ifndef __THREAD_POLL_H
#define __THREAD_POLL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <assert.h>
#include <sys/syscall.h>

typedef struct worker
{
	/*回调函数，任务运行时会调用此函数，注意也可声明成其它形式*/
	void *(*process)(void *arg);
	void *arg;	/*回调函数的参数*/
	struct worker *next;
} CThread_worker;

/*线程池结构*/
typedef struct
{
    pthread_mutex_t queue_lock;
    pthread_cond_t queue_ready;
    /*链表结构，线程池中所有等待任务*/
    CThread_worker *queue_head;
    /*是否销毁线程池*/
    int shutdown;
    pthread_t *threadid;
    /*线程池中允许的活动线程数目*/
    int max_thread_num;
    /*当前等待队列的任务数目*/
    int cur_queue_size;
} CThread_pool;

void *thread_routine(void* arg);
int pool_add_worker(void *process(void*),void*);

static CThread_pool *poll = NULL;	//静态全局变量，指向线程池的头

void poll_init(int max_thread_num)
{
	//给poll分配空间
	poll = (CThread_pool*)malloc(sizeof(CThread_pool));
	//动态分配线程id数组
	poll->threadid = (pthread_t*)malloc(sizeof(pthread_t)*max_thread_num);
	
	poll->queue_head = NULL;
	pthread_mutex_init(&(poll->queue_lock),NULL);
	pthread_cond_init(&(poll->queue_ready),NULL);
	
	poll->shutdown = 0;
	poll->max_thread_num = max_thread_num;
	poll->cur_queue_size = 0;
	
	int i = 0;
	//预先创建 max_thread_num个线程
	for(i = 0;i<max_thread_num;i++)
	{
		pthread_create(&poll->threadid[i],NULL,thread_routine,NULL);
	}
}

int poll_add_worker(void *(*process)(void*),void* arg)
{
	//创建一个新工作任务
	CThread_worker *newWorker = (CThread_worker*)malloc(sizeof(CThread_worker));
	
	//CThread_worker结构体保存的是新任务的具体情况
	newWorker->process = process;
	newWorker->arg = arg;
	newWorker->next = NULL;
	
	pthread_mutex_lock(&(poll->queue_lock));
	
	//将任务加入到队列
	CThread_worker* tmp = poll->queue_head;
	if(tmp == NULL)		//目前为空
		poll->queue_head = newWorker;
	else				//加入到队列的尾端
	{
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = newWorker;
	}
	//断言很好用
	assert(poll->queue_head != NULL);
	
	poll->cur_queue_size++;
	pthread_mutex_unlock(&(poll->queue_lock));
	
	//发送一个激活信号******
	pthread_cond_signal(&(poll->queue_ready));
}

void* thread_routine(void* arg)
{
	printf("start thread ID is :%d\n",syscall(SYS_gettid));
	while(1)
	{
		pthread_mutex_lock(&(poll->queue_lock));
		
		while(poll->cur_queue_size == 0 && poll->shutdown == 0)
		{
			printf("thread %d is waiting\n",syscall(SYS_gettid));
			//等待信号就绪
			pthread_cond_wait(&poll->queue_ready,&poll->queue_lock);	
		}

		if(poll->shutdown == 1)
		{
			pthread_mutex_unlock(&poll->queue_lock);
			printf("thead %d is exit\n",syscall(SYS_gettid));
			pthread_exit(0);
		}

		printf("thread %d starting work\n",syscall(SYS_gettid));
		assert(poll->cur_queue_size != 0);
		assert(poll->queue_head != NULL);

		//取出队列头
		poll->cur_queue_size--;
		CThread_worker* tmp = poll->queue_head;
		poll->queue_head = tmp->next;
		pthread_mutex_unlock(&poll->queue_lock);
		
		(*(tmp->process))(tmp->arg);
		free(tmp);
		tmp = NULL;
	}
}

//销毁线程池
int poll_destroty()
{
	if(poll->shutdown)		//防止被调用2次
		return -1;
	int  i =0;
	poll->shutdown = 1;
	
	pthread_cond_broadcast(&poll->queue_ready);	//唤醒所有线程（阻塞的线程如何退出？？？？)
	for(i = 0;i<poll->max_thread_num;i++)
		pthread_join(poll->threadid[i],NULL);
	free(poll->threadid);
	CThread_worker* head = poll->queue_head;
	while(head)
	{
		CThread_worker* next = head->next;
		free(head);
		head = NULL;
		head = next;
	}
	
	//释放条件变量和互斥锁
	pthread_mutex_destroy(&poll->queue_lock);
	pthread_cond_destroy(&poll->queue_ready);
	
	free(poll);
	poll = NULL;
}

#endif
