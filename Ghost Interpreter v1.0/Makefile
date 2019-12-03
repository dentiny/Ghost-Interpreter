CC = g++
CFLAGS = -std=c++11 -Werror -Wall -g3

Ghost: Ghost.cpp Ghost_intObj.o Ghost_floatObj.o Ghost_stringObj.o Ghost_listObj.o Parser.o DataManager.o ScopeManager.o
	$(CC) $(CFLAGS) Ghost.cpp -o Ghost Ghost_intObj.o Ghost_floatObj.o Ghost_stringObj.o Ghost_listObj.o Parser.o DataManager.o ScopeManager.o

Ghost_intObj.o: Ghost_intObj.cpp Ghost_floatObj.cpp Ghost_stringObj.cpp
	$(CC) $(CFLAGS) -c Ghost_intObj.cpp

Ghost_floatObj.o: Ghost_floatObj.cpp Ghost_intObj.cpp Ghost_stringObj.cpp
	$(CC) $(CFLAGS) -c Ghost_floatObj.cpp

Ghost_stringObj.o: Ghost_stringObj.cpp Ghost_intObj.cpp Ghost_floatObj.cpp
	$(CC) $(CFLAGS) -c Ghost_stringObj.cpp

Ghost_listObj.o: Ghost_listObj.cpp Ghost_intObj.cpp Ghost_floatObj.cpp Ghost_stringObj.cpp
	$(CC) $(CFLAGS) -c Ghost_listObj.cpp

ScopeManager.o: ScopeManager.cpp DataManager.cpp Ghost_intObj.cpp Ghost_floatObj.cpp Ghost_stringObj.cpp Ghost_listObj.cpp
	$(CC) $(CFLAGS) -c ScopeManager.cpp

DataManager.o: DataManager.cpp ScopeManager.cpp Ghost_intObj.cpp Ghost_floatObj.cpp Ghost_stringObj.cpp Ghost_listObj.cpp
	$(CC) $(CFLAGS) -c DataManager.cpp

Parser.o: Parser.cpp DataManager.cpp Ghost_intObj.cpp Ghost_floatObj.cpp Ghost_stringObj.cpp Ghost_listObj.cpp
	$(CC) $(CFLAGS) -c Parser.cpp

clean:
	rm -f *.o Ghost
