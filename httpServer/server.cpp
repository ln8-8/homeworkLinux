#include "server.h"

void Server::sendResponse(int clientFd) {
  handleFunctionality->handle(request, response);
  std::string headInStr;
  char buffer[1000];
  ssize_t respStatSize = response.status.size();
  for(int i = 0; i < respStatSize; i++) {
    buffer[i] = response.status[i];
  }
  buffer[respStatSize] = '\n';
  for (auto const &pair: request.head) {
    headInStr+=pair.first;
    headInStr+=":";
    headInStr+=" ";
    headInStr+=pair.second;
    headInStr+='\n';
  }
  for(int j = respStatSize + 1; j < headInStr.size() + respStatSize + 1; j++) {
    buffer[j] = response.status[j];
  }
  buffer[headInStr.size() + respStatSize + 1] = '\n';
  int bufSize = respStatSize + headInStr.size() + 2 + response.body.size();
  for(int k = respStatSize + headInStr.size() + 2; k < bufSize; k++){
    buffer[k] = request.body[k];
  }
  ssize_t writedInSocket = write(clientFd, buffer, bufSize);
  if(writedInSocket < 0) {
    std::cerr << "Could not write to client socket" << std::endl;
    exit(errno);
  }
}

void Server::getHandlerStruct(Handler *handler) {
  handleFunctionality = handler;
}

void Server::constructHead(std::string headStr) {
  std::string headKay;
  std::string headValue;
  int keyEndInd;
  for(int keyI = 0; keyI < headStr.size(); keyI++){
    if(headStr[keyI] != ':'){
      headKay += headStr[keyI];
    } else {
      keyEndInd = keyI;
      break;
    }
  }
  for(int valueI = keyEndInd + 2; valueI < headStr.size(); valueI++) {
    headValue += headStr[valueI];
  }
  request.head[headKay] = headValue;
}

void Server::getRequest(int clientFd) {
  char sentInfo[1000];
  ssize_t sentInfoSize = recv (clientFd, sentInfo, 1000, 0);
  if (sentInfoSize < 0) {
    std::cerr << "Could not read from client socket" << std::endl;
    exit(errno);
  }
  bool statusInd = false;
  bool headInd = false;
  std::string headStr;
  for(int charInd = 0; charInd < sentInfoSize; charInd++){
    if(!statusInd) {
      if(sentInfo[charInd] != '\n'){
        request.status += sentInfo[charInd];
      } else {
        statusInd = true;
      }
    } else if (!headInd) {
      if(sentInfo[charInd] != '\n'){
        headStr += sentInfo[charInd];
      } else if(sentInfo[charInd+1] != '\n'){
        constructHead(headStr);
        headStr.clear();
      } else {
        headInd = true;
        charInd++;
      }
    } else {
      if(sentInfo[charInd] != '\n'){
        request.body += sentInfo[charInd];
      }
    }
  }

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

    getRequest(clientFd);
    sendResponse(clientFd);
    close(clientFd);
  }

}
void staticSites::handle(fileInfo &request, fileInfo &response) {
  response.status = "HTTP1.1 200 OK";
  for (auto const &pair: request.head) {
    response.head[pair.first] = pair.second;
  }
  for(int i = 0; i < request.body.size(); i++){
    response.body[i] = request.body[i] + 1;
  }
}

void dynamicSites::handle(fileInfo &request, fileInfo &response) {

}