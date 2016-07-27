#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define HELLO_WORLD_SERVER_PORT 6666
#define LENGTH_OF_LISTEN_QUEUE 20
#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
  int opt = 1;
  struct sockaddr_in server_addr;
  bzero(&server_addr,sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htons(INADDR_ANY);
  server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);

  int server_socket = socket(AF_INET,SOCK_STREAM,0);
  if( server_socket < 0)
  {
    printf("Create Socket Failed!");
    exit(1);
  }

  setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));

  if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
  {
    printf("Server Bind Port : %d Failed!", HELLO_WORLD_SERVER_PORT);
    exit(1);
  }

  if ( listen(server_socket, LENGTH_OF_LISTEN_QUEUE) )
  {
    printf("Server Listen Failed!");
    exit(1);
  }

  while (1)
  {
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

    int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
    if ( new_server_socket < 0)
    {
      printf("Server Accept Failed!\n");
      break;
    }

    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);
    strcpy(buffer,"Hello,World from server!");
    strcat(buffer,"\n");
    send(new_server_socket,buffer,BUFFER_SIZE,0);

    bzero(buffer,BUFFER_SIZE);
    while(1){
      length = recv(new_server_socket,buffer,BUFFER_SIZE,0);
      if (length < 0)
      {
        printf("Server Recieve Data Failed!\n");
        exit(1);
      }else if(length == 0){
           //close(new_server_socket);
           break;
      }
      printf("\n%s",buffer);
      memset(buffer,0x00,BUFFER_SIZE);
    }
    close(new_server_socket);
  }
  close(server_socket);
  return 0;
}

