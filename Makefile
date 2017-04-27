CC = gcc
CFLAGS = -I. -Wall

binaries = mash

all: $(binaries)

clean:
	$(RM) -f $(binaries) *.o