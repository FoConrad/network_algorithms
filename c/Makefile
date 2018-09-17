CC := gcc
CFLAGS := -g -Wall -O0 -Wextra
INC := -I include
TARGET := run

SRC := $(shell find . -type f -name '*.c')

all: $(TARGET)

$(TARGET): $(SRC:%.c=%.o)
	$(CC) $^ -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm *.o $(TARGET)

.PHONY: clean all

