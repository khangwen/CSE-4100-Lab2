#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024

// Find Header Files and Put them here
// For example, #include <stdio.h>

// Please Add your remark at the ends of lines, line by line

int main(int argc, char *argv[])
{
  int serv_sock, clnt_sock;
  char message[BUF_SIZE];
  int str_len, i;
  struct sockaddr_in serv_adr;
  struct sockaddr_in clnt_adr;
  socklen_t clnt_adr_sz;

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_adr.sin_port = htons(atoi(argv[1]));
  bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr));
  listen(serv_sock, 5);
  clnt_adr_sz = sizeof(clnt_adr);
  clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);

  // Write a code to send a hello message to clinet after the connection is established.
  char buff[80];
  int n;

  for (;;)
  {
    bzero(buff, 80);

    read(clnt_sock, buff, sizeof(buff));

    printf("Client message : %s\t Send to client : ", buff);
    bzero(buff, 80);
    n = 0;
    while ((buff[n++] = getchar()) != '\n')
      ;
    write(clnt_sock, buff, sizeof(buff));

    if (strncmp("exit", buff, 4) == 0)
    {
      printf("Server Exiting...\n");
      break;
    }
  }

  close(clnt_sock);
  close(serv_sock);

  return 0;
}
