#makefile use muduo library
#2016/8/04 by wfp in hangzhou

DIRECTORY = /mnt/d/Code/muduo_setup
INCLUDE = $(DIRECTORY)/include
LIBRATY = $(DIRECTORY)/lib

CC = g++ -std=c++11
CFLAG = -I$(INCLUDE)
LDFLAG = -L$(LIBRATY) -lmuduo_net -lmuduo_base -lpthread -lrt

#main : main.o server.o
#	$(CC) -o $@ $^ $(LDFLAG)

#main.o : main.cpp
#	$(CC) $(CFLAG) -c $<
all : server client

server : server.o
	$(CC) -o $@ $^ $(LDFLAG)
	
server.o : server.cpp
	$(CC) $(CFLAG) -c $<
	
client : client.o
	$(CC) -o $@ $^ $(LDFLAG)
	
client.o : client.cpp
	$(CC) $(CFLAG) -c $<

.PHONY:clean
clean:
	rm *.o server client