/*
 * Service.h
 *
 *  Created on: May 2, 2019
 *      Author: puq81hc
 */

#ifndef SERVICE_SERVICE_H_
#define SERVICE_SERVICE_H_
#include <map>
#include <vector>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include "Topic.h"
#include "Client.h"
//for server implementation
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
//-----------------------------

class Service {
   public:
      Service();
     ~Service();
      //..................Server function............................
      void initServer(unsigned int port);
      void creatThreadPool(int numberOfThread);
      bool shutDownThreadPool(); //return true of all thread shutdowned
      void classifyMessage();
      //.............................................................

      bool topicRegister(const std::string &topicName, int clientFD = 0);
      bool createTopic(const std::string &topicName);

      void terminateTopicThread();
      void shutDownService();

      bool publishMessage( std::string topicName,std::string message,int clientFD);
      bool isTopicExists( const std::string &topicName);
      bool isClientExists(int clientFD);
   private:
      std::map<std::string,Topic* > TopicList;
      std::vector<std::thread> TopicThreads;
      std::map<std::string,Client* > ClientList;
      std::vector<std::thread> ClientThreads;

      std::vector<int>client_socket;
      std::list< std::pair<std::string,int> > messageQueue;
      std::vector<std::thread> threadPool;
      std::condition_variable m_cv;
      std::mutex m_mutex;
      std::thread m_server;
      bool m_shutDown;
      int shutDownPipe[2];
};

#endif /* SERVICE_SERVICE_H_ */
