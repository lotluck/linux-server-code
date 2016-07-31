/*==========================================================
     > File Name: alarm.c
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Sun 31 Jul 2016 07:27:32 PM CST
===========================================================*/
#include <unistd.h>
#include <signal.h>
#include <stdio.h>


void handler()
{
    printf("hello\n");
}

int main(int argc,char *argv[])
{
    int i = 0;
    signal(SIGALRM,handler);
    alarm(5);
    for( i = 1; i < 7; i++){
        printf("sleep %d.............\n",i);
        sleep(1);
    }
    return 0;
}
















