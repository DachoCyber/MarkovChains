CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = main.o chain.o
TARGET = program

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c chain.h
	$(CC) $(CFLAGS) -c main.c

chain.o: chain.c chain.h
	$(CC) $(CFLAGS) -c chain.c

clean:
	rm -f $(OBJ) $(TARGET)
