/*
 * Client.cpp
 *
 *  Created on: May 2, 2019
 *      Author: puq81hc
 */

#include "Client.h"

Client::Client(std::string name) {
   m_name = name;
   m_shutDown = false;
}

Client::~Client() {
   shutDownClient();
   m_data.clear();
   m_name.clear();
}

void Client::update() {
   while(1)
   {
      std::unique_lock<std::mutex> lock(m_mutex);
      Message mess(" "," ");
      m_cv.wait(lock,[this]{return (!m_data.empty() || m_shutDown);});
      if(m_shutDown){
         break;
      }
      mess = m_data.front();
      m_data.pop_front();
      mess.outputMessage(m_name);
   }
}
void Client::addMessage(std::string topic, std::string message) {
   std::lock_guard<std::mutex> guard(m_mutex);
   m_data.push_back({topic,message});
   m_cv.notify_one();
}

void Client::shutDownClient() {
   std::lock_guard<std::mutex> guard(m_mutex);
   m_shutDown = true;
   m_cv.notify_one();
}

const std::string& Client::getName() {
   return m_name;
}