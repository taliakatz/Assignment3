CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system
CFLAGS+= -pthread
LDFLAGS+= -pthread

all: Client

Client: bin/ClientMain.o bin/ClientDetails.o bin/ConnectionHandler.o bin/KeyBoardTask.o bin/ReadFromSocketTask.o bin/Tools.o
		g++ -o bin/StompBookClubClient bin/ClientDetails.o bin/ConnectionHandler.o bin/ClientMain.o bin/KeyBoardTask.o bin/ReadFromSocketTask.o bin/Tools.o $(LDFLAGS)


bin/ClientMain.o: src/ClientMain.cpp
	g++ $(CFLAGS) -o bin/ClientMain.o src/ClientMain.cpp


bin/ClientDetails.o: src/ClientDetails.cpp include/ClientDetails.h
	g++ $(CFLAGS) -o bin/ClientDetails.o src/ClientDetails.cpp


bin/ConnectionHandler.o: src/ConnectionHandler.cpp include/ConnectionHandler.h
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/KeyBoardTask.o: src/KeyBoardTask.cpp include/KeyBoardTask.h
	g++ $(CFLAGS) -o bin/KeyBoardTask.o src/KeyBoardTask.cpp

bin/ReadFromSocketTask.o: src/ReadFromSocketTask.cpp include/ReadFromSocketTask.h
	g++ $(CFLAGS) -o bin/ReadFromSocketTask.o src/ReadFromSocketTask.cpp

bin/Tools.o: src/Tools.cpp include/Tools.h
	g++ $(CFLAGS) -o bin/Tools.o src/Tools.cpp
run:
.PHONY: clean
clean:
	rm -f bin/*
