/*==========================================================
     > File Name: pause.c
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Sun 31 Jul 2016 07:46:43 PM CST
===========================================================*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void sig_alarm()
{
    printf("I love you\n");
}
int main()
{
    alarm(5);
    signal(SIGALRM,sig_alarm);
    pause();
    printf("I love you too\n");

    return 0;
}
















