#include "server.h"

void Server::response(int clientFd) {

}

void Server::request(int clientFd) {

}

void Server::run() {
  int serverFd = socket(AF_INET, SOCK_STREAM, 0);

  if(serverFd < 0){
    std::cerr << "Error while creating a socket" << std::endl;
    exit(errno);
  }

  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = htonl (INADDR_ANY);

  int bound = bind(serverFd, (const struct sockaddr*) &address, sizeof(address));

  if(bound < 0){
    std::cerr << "Could not bind to given port" << std::endl;
    exit(errno);
  }

  int listening = listen(serverFd, 1024);

  if(listening < 0){
    std::cerr << "Could not start listening" << std::endl;
    exit(errno);
  }

  while(true){
    sockaddr_in clientAddress;
    unsigned int clientAddressLength;
    int clientFd = accept(serverFd,(struct sockaddr*)  &clientAddress, &clientAddressLength);
    struct in_addr clientAddr = clientAddress.sin_addr;
    int clientPort = ntohs(clientAddress.sin_port);
    char* clientIp = inet_ntoa(clientAddr);

    int  number;
    ssize_t receivedBytes = recv(clientFd, (void*) &number, sizeof(number), 0);

    if(receivedBytes < 0){
      std::cerr << "Could not read from client. Error: " << strerror(errno) << std::endl;
      close(clientFd);
      continue;
    }

    request(clientFd);
    response(clientFd);
    close(clientFd);
  }

}