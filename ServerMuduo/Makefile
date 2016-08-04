#makefile use muduo library
#2016/8/04 by wfp in hangzhou

DIRECTORY = /mnt/d/Code/muduo_setup
INCLUDE = $(DIRECTORY)/include
LIBRATY = $(DIRECTORY)/lib

CC = g++ -std=c++11
CFLAG = -I$(INCLUDE)
LDFLAG = -L$(LIBRATY) -lmuduo_net -lmuduo_base -lpthread -lrt

main : main.o server.o
	$(CC) -o $@ $^ $(LDFLAG)

main.o : main.cpp
	$(CC) $(CFLAG) -c $<
server.o : server.cpp
	$(CC) $(CFLAG) -c $<

.PHONY:clean
clean:
	rm *.o main