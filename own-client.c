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
  address.sin_port = htons(PORT);

  int conn = connect(socket_descriptor, (struct sockaddr*) &address, sizeof(address));
  if (conn < 0) {
    perror("connect failed");
    exit(EXIT_FAILURE);
  }

  char* message = "Message from client.";
  send(socket_descriptor, message, strlen(message), 0);
  printf("Message \"%s\" sent.\n", message);

  char buffer[1024] = { 0 };
  read(socket_descriptor, buffer, 1024);
  printf("Message \"%s\" received.\n", buffer);

  close(conn);
  return 0;
}