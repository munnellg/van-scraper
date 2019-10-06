OBJS = $(wildcard src/*.cpp)

CC = g++

CFLAGS = -Wall -Wextra -Wpedantic -std=c++17 -rdynamic

LDFLAGS = -Iincludes -Wl,-Bsymbolic-functions -Wl,-z,relro -lstdc++ -ldl -lcurl -I/usr/local/include/raptor2 -I/usr/include/rasqal -lrdf -lrasqal -lraptor2 -I/usr/include/libxml2  -lxml2

BIN = scrape

all : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN) $(LDFLAGS)
