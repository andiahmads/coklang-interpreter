CC = gcc
CFLAGS="-Wall -g -fsanitize=address -I."
TARGET = repl
SOURCES = main.c repl.c lexer.c token.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
