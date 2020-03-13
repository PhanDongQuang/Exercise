VPATH = src include
CXX = g++ 
CXXFLAGS = -Wall  -std=c++11 -pthread -I include


All: Ex2 clean

Ex2: Ex2.o Message.o Client.o Service.o Topic.o 
	$(CXX)  $(CXXFLAGS) -o $@  $^
Ex2.o: Ex2.cpp Message.h Client.h Service.h Topic.h 
Message.o: Message.h
Client.o: Message.h Client.h 
Service.o: Message.h Topic.h Service.h
Topic.o: Message.h Client.h  Topic.h
clean:
	rm *.o

 vpath %.h include
 vpath %.c src