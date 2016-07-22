/*==========================================================
     > File Name: pthread_rwlock_test_one.c
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Fri 22 Jul 2016 10:11:55 AM CST
===========================================================*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <bits/pthreadtypes.h>
#include <string.h>
#include <unistd.h>

#define  WORK_SIZE     (1024)
static pthread_rwlock_t   rwlock;


char work_area[WORK_SIZE];
int  time_to_exit;


void *thread_read_to_one(void *arg);
void *thread_read_to_two(void *arg);
void *thread_write_to_one(void *arg);
void *thread_write_to_two(void *arg);


void  *thread_read_to_one(void *arg)
{
    printf("thread read 1  try to get lock\n");

    pthread_rwlock_rdlock(&rwlock);
    while(strncmp("end",work_area,3) != 0){
        printf("this is thread read one 11111111111111111 \n");
        printf("the characters is %s",work_area);
        pthread_rwlock_unlock(&rwlock);
        sleep(2);
        pthread_rwlock_rdlock(&rwlock);
        while(work_area[0] == '\0'){
            pthread_rwlock_unlock(&rwlock);
            sleep(2);
            pthread_rwlock_rdlock(&rwlock);
        }
    }
    pthread_rwlock_unlock(&rwlock);
    time_to_exit = 1;
    pthread_exit(0);
}

void *thread_read_to_two(void *arg)
{
    printf("thread read 2 try to get lock\n");

    pthread_rwlock_rdlock(&rwlock);
    while(strncmp("end",work_area,3) != 0){
        printf("this is thread two 22222222222222222222222\n");
        printf("the characters is %s",work_area);
        pthread_rwlock_unlock(&rwlock);
        sleep(5);
        pthread_rwlock_rdlock(&rwlock);
        while(work_area[0] == '\0'){
              pthread_rwlock_unlock(&rwlock);
              sleep(5);
              pthread_rwlock_rdlock(&rwlock);
        }
    }
    pthread_rwlock_unlock(&rwlock);
    time_to_exit = 1;
    pthread_exit(0);
}


void *thread_write_to_one(void *arg)
{
   printf("this is thread 1 try to get lock\n");
   while(!time_to_exit){
       pthread_rwlock_wrlock(&rwlock);
       printf("this is write thread one 11111111111111111\n,input some text,Entet 'end' to finish\n");
       fgets(work_area,WORK_SIZE,stdin);
       pthread_rwlock_unlock(&rwlock);
       sleep(15);
   }
   pthread_rwlock_unlock(&rwlock);
   pthread_exit(0);
}

void *thread_write_to_two(void *arg)
{
    printf("this is thread 2 try to get lock\n");
    sleep(10);
    while(!time_to_exit){
        pthread_rwlock_wrlock(&rwlock);
        printf("this is write thread two 22222222222222222222222\n,input some text,Enter 'end' to finish\n");
        fgets(work_area,WORK_SIZE,stdin);
        pthread_rwlock_unlock(&rwlock);
        sleep(20);
    }
    pthread_rwlock_unlock(&rwlock);
    pthread_exit(0);
}



int main(int argc,char *argv[])
{
    int retval;

    pthread_t a_thread,b_thread,c_thread,d_thread;
    void *thread_result;

    retval = pthread_rwlock_init(&rwlock,NULL);
    if(retval != 0){
        fprintf(stderr,"pthread_rwlock_init failed\n");
        exit(1);
    }

    retval = pthread_create(&a_thread,NULL,thread_read_to_one,NULL);
    if(retval != 0){
        fprintf(stderr,"pthread_create failed\n");
        exit(2);
    }

    retval = pthread_create(&b_thread,NULL,thread_read_to_two,NULL);
    if(retval != 0){
        fprintf(stderr,"pthread_create failed\n");
        exit(2);
    }

    retval = pthread_create(&c_thread,NULL,thread_write_to_one,NULL);
    if(retval != 0){
        fprintf(stderr,"pthread_create failed\n");
        exit(2);
    }

    retval = pthread_create(&d_thread,NULL,thread_write_to_two,NULL);
    if(retval != 0){
        fprintf(stderr,"pthread_create failed\n");
        exit(2);
    }



    retval = pthread_join(a_thread,&thread_result);
    if(retval != 0){
         fprintf(stderr,"pthread_join failed\n");
         exit(3);
    }

    retval = pthread_join(b_thread,&thread_result);
    if(retval != 0){
         fprintf(stderr,"pthread_join failed\n");
         exit(3);
    }

    retval = pthread_join(c_thread,&thread_result);
    if(retval != 0){
         fprintf(stderr,"pthread_join failed\n");
         exit(3);
    }

    retval = pthread_join(d_thread,&thread_result);
    if(retval != 0){
         fprintf(stderr,"pthread_join failed\n");
         exit(3);
    }

   pthread_rwlock_destroy(&rwlock);


    return 0;
}























































