//============================================================================
// Name        : Ex2.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include<signal.h>
#include<unistd.h>

#include "Client.h"
#include "Message.h"
#include "Service.h"


// void inputMessage(Service &service){
//    std::cout<<"********************GenerateMessage********************"<<std::endl;
//    while(!std::cin.eof()){
//       std::string m_message;
//       std::string m_topic;
//       do{
//          std::cout<<"choose a topic: ";
//          std::cin.clear();
//          std::getline(std::cin,m_topic);

//          if(!(service.isTopicExists(m_topic)))
//          {
//             std::cout<<"invalid topic"<<std::endl;
//          }
//          else
//          {
//             std::cout<<"input data: ";
//             std::cin.clear();
//             std::getline(std::cin,m_message);
//             service.publishMessage(m_topic,m_message);
//          }
//          std::cout<<"Press Enter to continue - Press Ctrl D to go to menu"<<std::endl;
//          std::cin.clear();
//          std::getline(std::cin,m_message);
//       }while(!std::cin.eof());



//    }
//    std::cout<<"******************************************************"<<std::endl;
// }
// void createClient(Service &service){
//    std::cout<<"********************CreateClient**********************"<<std::endl;
//    std::string clientName;
//    do{
//       std::cout<<"Enter client name: ";
//       std::cin.clear();
//       getline(std::cin,clientName);
//       if(!std::cin.eof())
//       {
//          if(!service.createClient(clientName))
//          {
//             std::cout<<"client existed"<<std::endl;
//          }
//          else
//          {
//             std::cout<<"Created client :"<<clientName<<"."<<std::endl;
//          }
//       }
//       else
//       {
//          std::cout<<" \n invalid name"<<std::endl;
//       }
//       std::cout<<"Press Enter to continue - Press Ctrl D to go to menu"<<std::endl;
//       std::getline(std::cin,clientName);
//    }while(!std::cin.eof());
//    std::cout<<"******************************************************"<<std::endl;
// }
// void registerTopic(Service &service){
//    std::cout<<"********************RegisterTopic**********************"<<std::endl;
//    std::string clientName;
//    std::string topicName;
//    do{
//       std::cout<<"Enter client name: ";
//       std::cin.clear();
//       getline(std::cin,clientName);

//       std::cout<<"Enter topic to subscribe: ";
//       std::cin.clear();
//       getline(std::cin,topicName);
//       std::cout<<std::endl;

//       if(service.topicRegister(topicName,clientName))
//       {
//          std::cout<<"client "<<clientName<<" subscribed to topic "<<topicName<<std::endl;;
//       }
//       else
//       {
//          std::cout<<"invalid client or topic"<<std::endl;
//       }

//       std::cout<<"Press Enter to continue - Press Ctrl D to go to menu"<<std::endl;
//       std::cin.clear();
//       std::getline(std::cin,clientName);

//    }while(!std::cin.eof());
//    std::cout<<"******************************************************"<<std::endl;
// }
// void createTopic(Service &service){
//    std::cout<<"********************CreateTopic**********************"<<std::endl;
//    std::string topicName;
//    do{
//       std::cout<<"Enter topic name: ";
//       std::cin.clear();
//       getline(std::cin,topicName);
//       if(!std::cin.eof()){
//          if(!service.createTopic(topicName))
//          {
//             std::cout<<"topic existed"<<std::endl;
//          }
//          else
//          {
//             std::cout<<"Created topic :"<<topicName<<"."<<std::endl;
//          }
//       }
//       else
//       {
//          std::cout<<" \n invalid name"<<std::endl;
//       }

//       std::cout<<"Press Enter to continue - Press Ctrl D to go to menu"<<std::endl;
//       std::cin.clear();
//       std::getline(std::cin,topicName);

//    }while(!std::cin.eof());
//    std::cout<<"*****************************************************"<<std::endl;
// }
void menu(Service &service){
   bool run = true;
   while(run){
      std::string option;
      std::cout<<"********************Menu******************************"<<std::endl;
      // std::cout<<"generate message  - press 1"<<std::endl;
      // std::cout<<"create new client - press 2"<<std::endl;
      // std::cout<<"create new topic  - press 3"<<std::endl;
      // std::cout<<"register topic    - press 4"<<std::endl;
      std::cout<<"exit program      - press 1"<<std::endl;
      std::cout<<"*******************************************************"<<std::endl;
      std::cout<<"Enter your option: ";
      std::cin.clear();
      std::getline(std::cin,option);
      if(option.compare("1") == 0 )
      {
         service.shutDownService();
         break;
      }
//       else if (option.compare("2") == 0)
//       {
//          createClient(service);
//       }
//       else if (option.compare("3") == 0)
//       {
//          createTopic(service);
//       }
//       else if (option.compare("4") == 0){
//          registerTopic(service);
//       }
//       else if (option.compare("5") == 0){
//          service.shutDownService();
//          run = false;
//       }
   }
}
int main() {
   Service m_service;
   m_service.initServer(8000);
  // menu(service);
   return 0;
}
