CC = clang
CFLAGS = -Wall

OBJS = functions.o main.o

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

functions.o: functions.c header.h
	$(CC) -c functions.c

main.o: main.c header.h
	$(CC) -c main.c

clean:
	rm -f $(OBJS) $(TARGET)
