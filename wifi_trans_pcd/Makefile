CC = g++ -std=c++11
CFLAG = -g
CPPFLAG = -I include

OBJ_SERVER = server.o
OBJ_CLIENT = client.o

#vpath 只对make起作用，对编译阶段是没用的
vpath %.h include
vpath %.cpp src
vpath %.c src

all: server client
.PHONY : all

server: $(OBJ_SERVER)
	$(CC) -o $@ $(OBJ_SERVER) -lpthread
	
client: $(OBJ_CLIENT)
	$(CC) -o $@ $(OBJ_CLIENT) -lpthread
	
%.o : %.cpp
	$(CC) $(CFLAG) $(CPPFLAG) -c $<

.PHONY : clean
clean:
	rm server client *.o
