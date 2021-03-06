#ifndef HTTPSERVER_LIBRARY_H
#define HTTPSERVER_LIBRARY_H
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <cerrno>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <map>

struct fileInfo {
  std::string status;
  std::map <std::string, std::string> head;
  std::string body;
};


class Handler {
 public:
  virtual void handle (fileInfo &request, fileInfo &response) = 0;
};

class staticSites : Handler {
 public:
  void handle (fileInfo &request, fileInfo &response) override;
};

class dynamicSites : Handler {
 public:
  void handle (fileInfo &request, fileInfo &response) override;
};

class Server {
  const int port = 9090;
  fileInfo request;
  fileInfo response;
  Handler *handleFunctionality;
public:
  Server() = default;
  void run();
  void getHandlerStruct(Handler* handler);
  void constructHead(std::string headStr);
  void getRequest(int clientFd);
  void sendResponse(int clientFd);
};

#endif //HTTPSERVER_LIBRARY_H
