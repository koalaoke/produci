TARGET = test_struct

CC = gcc

CFLAGS = -Wall -g

SRCS = test_struct.c structs.c

OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c structs.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.exe, *.o
