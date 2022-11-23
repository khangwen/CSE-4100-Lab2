#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_SIZE 1024

// Find Header Files and Put them here
// For example, #include <stdio.h>

// Please Add your remark at the ends of lines, line by line

int main(int argc, char *argv[])
{
  int sock;
  char message[BUF_SIZE];
  int str_len;
  struct sockaddr_in serv_adr;

  sock = socket(PF_INET, SOCK_STREAM, 0);

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_adr.sin_port = htons(atoi(argv[2]));

  connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr));

  // Write a code to receive a hello message from server and show the hello on the terminal after the connection is established.
  char buff[80];
  int n;

  for (;;)
  {
    bzero(buff, sizeof(buff));
    printf("Enter the message to send : ");
    n = 0;
    while ((buff[n++] = getchar()) != '\n')
      ;
    write(sock, buff, sizeof(buff));
    bzero(buff, sizeof(buff));
    read(sock, buff, sizeof(buff));
    if ((strncmp(buff, "exit", 4)) == 0)
    {
      printf("Exiting...\n");
      break;
    }
  }

  close(sock);

  return 0;
}
