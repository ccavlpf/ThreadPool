all:Thread

CC=g++
CPPFLAGS=-Wall -std=c++11 -ggdb
LDFLAGS=-pthread
Thread:main.o
	$(CC) $(LDFLAGS) -o $@ $^
main.o:main.cpp
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $@ -c $^

.PHONY:
	clean

clean:
	rm main.o Thread