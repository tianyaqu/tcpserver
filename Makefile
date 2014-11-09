CC		= gcc
CXX		= g++
LINK	= g++
LIBS	= -lboost_system
CPPFLAGS	= -g

TARGET	= server 
OBJECTS	= main.o acceptor.o channel.o tcpserver.o pollpoller.o eventloop.o



all:$(TARGET)

server:	$(OBJECTS)
	$(LINK) $(CLFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)
	cp server ~/

client:	$(OBJECTS)
	$(LINK) $(CLFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

clean:
	rm -rf *.o $(TARGET)
