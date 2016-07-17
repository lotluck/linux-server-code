/*==========================================================
     > File Name: duptest.c
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Sun 17 Jul 2016 08:44:48 AM CST
===========================================================*/

#include "ds_socket.h"

int main(int argc,char *argv[])
{
    int  sockfd;
    int  connfd;
    struct sockaddr_in  clientaddr;
    socklen_t  clientaddr_size = sizeof(clientaddr);


    sockfd = ds_create_socket();

    connfd = ds_accept(sockfd,(struct sockaddr*)(&clientaddr),&clientaddr_size);

    printf("client connect success.....\n");
    //close STDOUT_FILENO
    close(STDOUT_FILENO);
    dup(connfd);
    printf("I am very smart smart by dup\n ");
    sleep(5);
    close(connfd);
    close(sockfd);
    return 0;
}
