OBJS = $(wildcard src/*.cpp)

CC = g++

CFLAGS = -Wall -Wextra -Wpedantic -std=c++17 -rdynamic

LDFLAGS = -Iincludes -Wl,-Bsymbolic-functions -Wl,-z,relro -lstdc++ -ldl -lcurl -lxml2 -I/usr/include/libxml2

BIN = scrape

all : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN) $(LDFLAGS)
