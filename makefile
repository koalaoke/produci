<<<<<<< Updated upstream
TARGET = test_struct

CC = gcc
CFLAGS = -Wall -g

SRCS = test_struct.c structs.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c structs.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
=======
<<<<<<< HEAD
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
=======
TARGET = read_file.c

CC = gcc

CFLAGS = -Wall -g

SRCS = read_file.c

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) 

%.o: %.c structs.h
	$(CC) $(CFLAGS) -c $< -o $@

>>>>>>> 8175601c9fefa912a5af4a5b6ff01eca6f00470f
>>>>>>> Stashed changes
