/*==========================================================
     > File Name: sendfiletest.c
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Sun 17 Jul 2016 09:38:56 AM CST
===========================================================*/

#include "ds_socket.h"


int main(int argc,char *argv[])
{
    int sockfd;
    int connfd;
    int filefd;
    const char *file_name = argv[1];
    struct stat stat_buf;
    struct sockaddr_in client_addr;
    socklen_t   client_addr_length = sizeof(client_addr);

    sockfd = ds_create_socket();

    filefd = open(file_name,O_RDONLY);
    assert(filefd > 0);
    fstat(filefd,&stat_buf);

    connfd = ds_accept(sockfd,(struct sockaddr*)(&client_addr),&(client_addr_length));

    sendfile(connfd,filefd,NULL,stat_buf.st_size);

    sleep(15); 

    close(connfd);

    close(sockfd);

    return 0;
}

