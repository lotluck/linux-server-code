/*==========================================================
     > File Name: timer.c
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Sun 31 Jul 2016 09:51:17 PM CST
===========================================================*/

#include <sys/time.h>
#include <sys/select.h>
#include <time.h>
#include <stdio.h>

void setTimer(int seconds,int mseconds)
{
    struct timeval temp;

    temp.tv_sec = seconds;
    temp.tv_usec = mseconds;

    select(0,NULL,NULL,NULL,&temp);
    printf("timer\n");
}



int main()
{
   int i = 0;

   for(i = 0; i < 100; i++){
       setTimer(1,0);
   }
   return 0;
}


