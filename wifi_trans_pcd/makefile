all: server client

cc = g++ -std=c++11
INCLUDE = ./include
SRC = ./src

server: server.o
	$(cc) -o server server.o -lpthread
client: client.o
	$(cc) -o client client.o -lpthread
	
server.o: $(INCLUDE)/thread_poll.h $(INCLUDE)/common.h $(INCLUDE)/server.h $(SRC)/server.cpp
	$(cc) -g -c $(SRC)/server.cpp -I $(INCLUDE) 
	
client.o: $(SRC)/client.c $(INCLUDE)/client.h $(INCLUDE)/common.h
	$(cc) -g -c $(SRC)/client.c -I $(INCLUDE)/

clean:
	rm server client *.o
