CC		= gcc
CXX		= g++
LINK	= g++
LIBS	= -lboost_system

TARGET	= server 
OBJECTS	= main.o acceptor.o channel.o tcpserver.o pollpoller.o eventloop.o



all:$(TARGET)

server:	$(OBJECTS)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

client:	$(OBJECTS)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)
