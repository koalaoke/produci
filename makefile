TARGET = read_file.c

CC = gcc

CFLAGS = -Wall -g

SRCS = read_file.c

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) 

%.o: %.c structs.h
	$(CC) $(CFLAGS) -c $< -o $@

