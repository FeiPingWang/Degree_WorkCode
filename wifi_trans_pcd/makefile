all: server client
cc = gcc

server: server.o
	$(cc) -o server server.o -lpthread
client: client.o
	$(cc) -o client client.o -lpthread

server.o:server.c
	$(cc) -g -c server.c
client.o: client.c
	$(cc) -g -c client.c

clean:
	rm server client *.o
