OBJS = $(wildcard src/*.cpp)

CC = g++

CFLAGS = -Wall -Wextra -Wpedantic -std=c++17 -shared -fPIC 

LDFLAGS = -I../scraper/includes -lcurl -lxml2 -I/usr/include/libxml2 -I/usr/local/include/raptor2 -I/usr/include/rasqal -lrdf -lraptor2

BIN = van-monster.so

all : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN) $(LDFLAGS)
