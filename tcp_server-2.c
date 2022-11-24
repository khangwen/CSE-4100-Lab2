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
  int serv_sock, clnt_sock;    // default declaration of welcoming socket and client socket
  char message[BUF_SIZE];      // default declaration of message to be sent
  int str_len, i;              // default declaration of size of message
  struct sockaddr_in serv_adr; // create structure for server address
  struct sockaddr_in clnt_adr; // create structure for client address
  socklen_t clnt_adr_sz;       // default declaration for client address size

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);                               // create TCP socket with domain IPv4 and default protocol
  memset(&serv_adr, 0, sizeof(serv_adr));                                    // fill memory with server address info
  serv_adr.sin_family = AF_INET;                                             // fill domain info
  serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);                              // fill server address
  serv_adr.sin_port = htons(atoi(argv[1]));                                  // fill server port
  bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr));           // bind welcoming socket to server address
  listen(serv_sock, 5);                                                      // server put in waiting state until conection with client established
  clnt_adr_sz = sizeof(clnt_adr);                                            // client address assigned value
  clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz); // data packet is accepted

  // Write a code to send a hello message to client after the connection is established.
  char buff[1024]; // declare buffer message with size 80
  strncpy(buff, "Hello", 1024);
  int n; // number to check for blank input

  write(clnt_sock, buff, sizeof(buff)); // buffer message sent to client

  close(clnt_sock); // close client socket
  close(serv_sock); // close welcoming socket

  return 0;
}
