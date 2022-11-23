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
  int sock;                    // default declaration of client socket
  char message[BUF_SIZE];      // default declaration of message to be sent
  int str_len;                 // default declaration of size of message
  struct sockaddr_in serv_adr; // create structure for server address

  sock = socket(PF_INET, SOCK_STREAM, 0); // crete TCP socket with domain IPv4 and default protocol

  memset(&serv_adr, 0, sizeof(serv_adr));        // fill memory with server address info
  serv_adr.sin_family = AF_INET;                 // fill domain info
  serv_adr.sin_addr.s_addr = inet_addr(argv[1]); // fill server address
  serv_adr.sin_port = htons(atoi(argv[2]));      // fill server port

  connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)); // client socket connects to server

  // Write a code to receive a hello message from server and show the hello on the terminal after the connection is established.
  char buff[80]; // buffer of size 80 created
  int n;         // number created for loading buffer

  // infinite loop created to send message to server
  for (;;)
  {
    bzero(buff, sizeof(buff));              // memory filled with buffer of size 80
    printf("Enter the message to send : "); // output message to terminal to request string input
    n = 0;                                  // number set to 0
    while ((buff[n++] = getchar()) != '\n') // string input stored into buffer, checks for empty string
      ;
    write(sock, buff, sizeof(buff));     // client sends message to server
    bzero(buff, sizeof(buff));           // fill memory with buffer
    read(sock, buff, sizeof(buff));      // client reads message sent back from server
    if ((strncmp(buff, "exit", 4)) == 0) // if input is "exit", exit out of loop to close socket
    {
      printf("Exiting...\n");
      break;
    }
  }

  close(sock); // client socket closed

  return 0;
}
