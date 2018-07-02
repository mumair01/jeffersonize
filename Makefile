# Makefile for CAlite2CHAT

CC = clang++
CFLAGS = -Wall -Wextra -c -std=c++11 -O2
DEPS = converter.h ca_chat.h chat_ca.h

%.o: %.cpp $(DEPS)
		$(CC) -o $@ $< $(CFLAGS)

all: converter clean

converter: driver2.0.o converter.o ca_chat.o chat_ca.o
		$(CC) -o converter driver2.0.o converter.o ca_chat.o chat_ca.o

clean:
		rm -f *.o core *~ driver2.0.o converter.o ca_chat.o chat_ca.o
