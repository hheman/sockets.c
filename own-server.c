#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 3001

int main(int argc, char const* argv[]) {
  struct sockaddr_in address;
  int address_size = sizeof(address);
  int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  int b = bind(socket_descriptor, (struct sockaddr*) &address, sizeof(address));
  if (b < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  int l = listen(socket_descriptor, 3);
  if (l < 0) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }

  int conn = accept(socket_descriptor, (struct sockaddr*) &address, (socklen_t*) &address_size);
  if (conn < 0) {
    perror("accept failed");
    exit(EXIT_FAILURE);
  }

  char buffer[1024] = { 0 };
  read(conn, buffer, 1024);
  printf("Message \"%s\" received.\n", buffer);

  char* message = "Message from server.";
  send(conn, message, strlen(message), 0);  
  printf("Message \"%s\" sent.\n", message);

  close(conn);
  shutdown(socket_descriptor, SHUT_RDWR);

  return 1;
}