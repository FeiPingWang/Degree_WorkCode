all: server client testclient
cc = gcc

server: server.o
	$(cc) -o server server.o -lpthread
client: client.o
	$(cc) -o client client.o -lpthread
testclient: test_client.o
	$(cc) -o testclient test_client.o -lpthread
	
server.o: ./thread_poll.h server.c
	$(cc) -g -c server.c -I . 
client.o: client.c
	$(cc) -g -c client.c
test_client.o: test_client.c
	$(cc) -g -c test_client.c

clean:
	rm server client testclient *.o
