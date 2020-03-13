/*
 * Topic.h
 *
 *  Created on: May 7, 2019
 *      Author: puq81hc
 */

#ifndef EXERCISE2_TOPIC_TOPIC_H_
#define EXERCISE2_TOPIC_TOPIC_H_
#include <algorithm>
#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <chrono>
#include "Client.h"
#include "Message.h"
// #include <sys/types.h>
// #include <sys/socket.h>

class Topic {
   public:
      Topic();
      ~Topic();
      void registerClient(int clientFD);
      void notifyClient();
      void addMessage(std::string message,int clientFD);
      void shutDownTopic();

   private:
      std::list<int> clients;
      std::list<std::pair<std::string,int> >messageQueue;
      std::condition_variable m_cv;
      std::mutex m_mutex;
      bool m_shutDown;
};

#endif /* EXERCISE2_TOPIC_TOPIC_H_ */
