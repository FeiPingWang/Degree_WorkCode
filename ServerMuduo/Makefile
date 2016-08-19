#makefile use muduo library
#2016/8/04 by wfp in hangzhou

DIRECTORY = /mnt/d/Code/muduo_setup
INCLUDE = $(DIRECTORY)/include
LIBRATY = $(DIRECTORY)/lib

CC = g++ -g
CFLAG = -I$(INCLUDE)
LDFLAG = -L$(LIBRATY) -lmuduo_net -lmuduo_base -lpthread -lrt

all : mainServer mainClient

mainServer : mainServer.o server.o
	$(CC) -o $@ $^ $(LDFLAG)
	
mainClient : mainClient.o client.o
	$(CC) -o $@ $^ $(LDFLAG)
	
mainServer.o : mainServer.cpp
	$(CC) $(CFLAG) -c $<
	
server.o : server.cpp
	$(CC) $(CFLAG) -c $<
	
mainClient.o : mainClient.cpp
	$(CC) $(CFLAG) -c $<
	
client.o : client.cpp
	$(CC) $(CFLAG) -c $<

.PHONY:clean
clean:
	rm *.o mainServer mainClient