/*
 * Topic.cpp
 *
 *  Created on: May 7, 2019
 *      Author: puq81hc
 */

#include "Topic.h"
//.............
#include <iostream>

Topic::Topic() {
   m_shutDown = false;
}
void Topic::registerClient(int clientFD) {

   std::list<int>::iterator findIter = std::find(clients.begin(), clients.end(), clientFD);
   if(findIter == clients.end()){
      clients.push_back(clientFD);
   }
}

void Topic::notifyClient() {
   // Message mess(" "," ");

   while(true){
      std::unique_lock<std::mutex> lock(m_mutex);
      m_cv.wait(lock, [this]{return !messageQueue.empty() || m_shutDown;});
    
      if(m_shutDown){
         break;
      }

      std::string message = messageQueue.front().first;
      int clientFD = messageQueue.front().second;
      messageQueue.pop_front();
      lock.unlock();

      for(auto m_clientFD : clients ){
         if(m_clientFD != clientFD)
         {
          //  send(m_clientFD, &message, sizeof(message),0); 
         }
      }
    }
}

void Topic::addMessage(std::string message,int clientFD) {
   std::lock_guard<std::mutex> guard(m_mutex);
   messageQueue.push_back({message,clientFD});
   m_cv.notify_one();
}

Topic::~Topic() {
   shutDownTopic();
   messageQueue.clear();
   clients.clear();
}

void Topic::shutDownTopic() {
   std::lock_guard<std::mutex> guard(m_mutex);
   m_shutDown = true;
   m_cv.notify_one();
}
