/*
 * Service.cpp
 *
 *  Created on: May 2, 2019
 *      Author: puq81hc
 */

#include "Service.h"

Service::Service() {

   m_shutDown = false;
  
   creatThreadPool(3);
  
  // m_server = std::thread (&Service::initServer,this,8000);
  // m_server.detach();

   std::string topicA = "A";
   std::string topicB = "B";
   std::string topicC = "C";

   createTopic(topicA);
   createTopic(topicB);
   createTopic(topicC);

}

Service::~Service() {
   shutDownService();
   for ( auto it = TopicList.begin(); it != TopicList.end(); ++it  )
   {
      delete it->second;
   }

   TopicList.clear();
}
void Service::initServer(unsigned int port) {

   int master_socket,
    addrlen , new_socket 
   , activity
   , valread 
   , sd;
   int max_sd;
   struct sockaddr_in address;
   char buffer[1025];
   fd_set readfds;

   if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
   {
      exit(EXIT_FAILURE);
   }

   int tr =1;
   if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, &tr, sizeof(int)) == -1 )
   {
      exit(EXIT_FAILURE);
   }

   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons( port );
   

   if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
   {
      perror("bind failed");
      exit(EXIT_FAILURE);
   }
   printf("Listener on port %d \n", port);

   if (listen(master_socket, 3) < 0)
   {
      perror("listen");
      exit(EXIT_FAILURE);
   }

   addrlen = sizeof(address);
   puts("Waiting for connections ...");
   
   

   while(!m_shutDown)
   {
      FD_ZERO(&readfds);
      FD_SET(master_socket, &readfds);

      max_sd = master_socket;

      for ( auto client :client_socket)
      {
         if( client > 0 )
         {
            std::cout<<"client: "<<client<<std::endl;
            FD_SET( client, &readfds);
            max_sd = std::max(max_sd,client);
         } 
      }

      
      activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

      if ((activity < 0) && (errno!=EINTR))
      {
         printf("select error");
      }

      // if(FD_ISSET(shutDownPipe[0],&readfds)){
      //    std::cout<<"server down"<<std::endl;
      //    break;
      // }

      if (FD_ISSET(master_socket, &readfds))
      {
         if ((new_socket = accept(master_socket,(struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
         {
            perror("accept");
            exit(EXIT_FAILURE);
         }

         printf("New connection , socket fd is %d , ip is : %s , port : %d n" , new_socket , inet_ntoa(address.sin_addr) ,ntohs (address.sin_port));

         // if( send(new_socket, message, strlen(message), 0) != strlen(message) )
         // {
         //    perror("send");
         // }

         client_socket.push_back(new_socket);
         std::cout<<"Added to list of sockets as: "<< (client_socket.size()-1)<<std::endl;
      }

      for (auto m_client : client_socket)
      {
         
         sd = m_client;

         if (FD_ISSET( sd , &readfds))
         {
            valread = recv( sd , buffer, sizeof(buffer), 0);
            if (valread == 0)
            {
               getpeername(sd , (struct sockaddr*)&address ,(socklen_t*)&addrlen);
               printf("Host disconnected , ip %s , port %d \n" ,inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
               close( sd );
               m_client = 0;
            }
            else
            {   
               std::lock_guard<std::mutex> guard(m_mutex);
               std::cout<<"Having message"<<std::endl;
               printf("From client: %s",buffer);
               messageQueue.push_back({buffer,sd});
               m_cv.notify_all();
            }
         }
      }
   }
}

void Service::creatThreadPool(int numberofthread) {
   for (int i = 0 ; i < numberofthread ; i++)
   {
      threadPool.push_back( std::thread(&Service::classifyMessage,this) );
   }   
}

void Service::classifyMessage() {

   while(true){
      std::string message;
      int _clientFD;
      std::unique_lock<std::mutex> lock(m_mutex);
      m_cv.wait(lock, [this]{return !messageQueue.empty() || m_shutDown;});

      if(m_shutDown)
      {
         break;
      }
      std::cout<<"hello im in"<<std::endl;
      _clientFD = messageQueue.front().second;
      message = messageQueue.front().first;
      messageQueue.pop_front();
      lock.unlock();

      if ( message.find("__TR") == 0 ) //__TR_topic
      {
         //call registertopic
         message = message.substr(4,message.size()-1);
         std::string topic = message.substr(0,message.size()-1);
          std::cout<<"hello im in 2: "<<topic<<std::endl;
         topicRegister(topic,_clientFD);
      } 
      
      else//Topic_message
      {
         unsigned int pos1 = message.find('_');
         std::string topic = message.substr(0,pos1);
         std::cout<<"Message: "<<message<<std::endl;
         publishMessage(topic,message,_clientFD);
      }
      
   }

}
bool Service::topicRegister(const std::string &topicName,int clientFD) {
   std::cout<<"hello im in 4 "<<topicName <<std::endl;
   if(isTopicExists(topicName))
   {
       std::cout<<"hello im in 3"<<std::endl;
      TopicList[topicName]->registerClient(clientFD);
      return true;
   }
   else
   {
      return false;
   }
}

void Service::shutDownService() {
   
   terminateTopicThread();
   m_shutDown = true;
   //write(shutDownPipe[1],"ShutDown",sizeof("ShutDown")); 
   //m_server.join();

}

bool Service::isTopicExists(const std::string &topicName) {
   return (TopicList.find(topicName) != TopicList.end());
}

bool Service::publishMessage(std::string topicName,std::string message,int clientFD) {

   if(isTopicExists(topicName))
   {
      TopicList[topicName]-> addMessage(message,clientFD);
      return true;
   }
   return false;
}

void Service::terminateTopicThread() {
   for ( auto it = TopicList.begin(); it != TopicList.end(); ++it  )
   {
      it->second->shutDownTopic();
   }
   for ( auto it = TopicThreads.begin(); it != TopicThreads.end(); ++it  )
   {
      it->join();
   }
   TopicThreads.clear();
}

bool Service::createTopic(const std::string &topicName) {
   if(isTopicExists(topicName)){
         return false;
   }
   Topic *newTopic = new Topic;
   TopicList.insert({topicName,newTopic});
   TopicThreads.push_back( std::thread(&Topic::notifyClient,TopicList[topicName] ) );
   return true;
}

bool Service::isClientExists(int clientFD) {
   return  std::find(client_socket.begin(),client_socket.end(),clientFD) == client_socket.end();
}
