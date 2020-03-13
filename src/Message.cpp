/*
 * Message.cpp
 *
 *  Created on: May 2, 2019
 *      Author: puq81hc
 */

#include "Message.h"

Message::Message( std::string topic,std::string data){
   m_topic = topic;
   m_data = data;
}

Message::~Message() {
   m_topic.clear();
   m_data.clear();
}

std::string Message::getTopic() {
   return m_topic;
}

std::string Message::getMessage() {
   return m_data;
}

void Message::outputMessage(std::string clientName) {
   std::cout<<clientName<<" : "<<m_data<<std::endl;
}

