#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// Find Header Files and Put them here
// For example, #include <stdio.h>

// Please Add your remark at the ends of lines, line by line

int main(){
  int sock;
  char message[BUF_SIZE];
  int str_len;
  struct sockaddr_in serv_adr;

  sock=socket(PF_INET, SOCK_STREAM, 0);   

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family=AF_INET;
  serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
  serv_adr.sin_port=htons(atoi(argv[2]));
    
  connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) 	

  // Modify the code from here
  write(sock, message, strlen(message));
  str_len=read(sock, message, BUF_SIZE-1);
  // Modify the code till here
  
  close(sock);

  return 0;
}
