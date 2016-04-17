#copyright by FeiPingWang in 2016/04/17
#ddd`dadja
DIR = ./src/
LIB = ./lib/
cc = g++ --std = c++11
Object = TextQuery.o runQueryTest.o QueryResult.o
edit : $(Object)
	cc -o edit $(Object)
runQueryTest.o : $(DIR)runQueryTest.cpp $(LIB)TextQuery.h $(LIB)QueryResult.h
	cc -c $(DIR)runQueryTest.cpp -I$(LIB)
TextQuery.o : $(DIR)TextQuery.cpp $(LIB)TextQuery.h $(LIB)QueryResult.h
	cc -c $(DIR)TextQuery.cpp -I$(LIB)
QueryResult.o : $(DIR)QueryResult.cpp $(LIB)QueryResult.h
	cc -c $(DIR)QueryResult.cpp -I$(LIB)

