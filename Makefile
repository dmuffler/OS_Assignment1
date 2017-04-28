CC = gcc
CFLAGS = -Wall

binaries = mash

all: $(binaries)

clean:
	$(RM) -f $(binaries) *.o