CC = gcc
# -g : allows use of GNU Debugger
# -Wall : show all warnings
CFLAGS = -g -Wall -Werror
LIBS = -pthread
SOURCE = common.c producer.c consumer.c main.c
OUTPUT = main

all: $(SOURCE)
	$(CC) $(LIBS) $(CFLAGS) -o $(OUTPUT) $(SOURCE)

clean:
	@rm -f $(OUTPUT)
