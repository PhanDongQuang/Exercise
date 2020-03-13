/*
 * Client.h
 *
 *  Created on: May 2, 2019
 *      Author: puq81hc
 */

#ifndef CLIENT_CLIENT_H_
#define CLIENT_CLIENT_H_
#include <list>
#include <thread>
#include <condition_variable>
#include <mutex>
#include "Message.h"

class Client {
   public:
      Client(std::string name);
      ~Client();
      void update();
      void addMessage(std::string topic, std::string message);
      void shutDownClient();
      const std::string& getName();

   private:
      std::mutex m_mutex;
      std::condition_variable m_cv;
      std::list<Message> m_data;
      std::string m_name;
      bool m_shutDown;
};

#endif /* CLIENT_CLIENT_H_ */
