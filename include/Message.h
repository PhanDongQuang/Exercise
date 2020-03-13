/*
 * Message.h
 *
 *  Created on: May 2, 2019
 *      Author: puq81hc
 */

#ifndef MESSAGE_MESSAGE_H_
#define MESSAGE_MESSAGE_H_
#include <iostream>

class Message {
   public:
      Message(std::string topic,std::string data);
      ~Message();
      std::string getTopic();
      std::string getMessage();
      void outputMessage(std::string clientName);

   private:
      std::string m_topic;
      std::string m_data;
};

#endif /* MESSAGE_MESSAGE_H_ */
