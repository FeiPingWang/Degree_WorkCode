all: server client testclient
cc = g++ -std=c++0x
#cc = gcc
server: server.o
	$(cc) -o server server.o -lpthread
client: client.o
	$(cc) -o client client.o -lpthread
#testclient: test_client.o
#	$(cc) -o testclient test_client.o -lpthread
	
server.o: ./thread_poll.h ./common.h server.cpp
	$(cc) -g -c server.cpp -I . 
client.o: client.c ./common.h
	$(cc) -g -c client.c -I .i
#test_client.o: test_client.c
#	$(cc) -g -c test_client.c

clean:
	rm server client *.o
