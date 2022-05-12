#ifndef HTTPSERVER_LIBRARY_H
#define HTTPSERVER_LIBRARY_H
#include "server.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <cerrno>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>

class Server {
  const int port = 9090;
public:
  Server() = default;
  void run();
  void request(int clientFd);
  void response(int clientFd);
};


#endif //HTTPSERVER_LIBRARY_H
