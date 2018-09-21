CC := gcc
CFLAGS := -g -Wall -O0 -Wextra
INC = -Iinclude
TARGET := run

SRCDIR := src
OBJDIR := build

SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

MAIN = main

all: $(TARGET)
lib: set_o2 $(OBJ)

# When making lib, set o2
set_o2:
	$(eval CFLAGS = -O2)

$(TARGET): $(OBJ) $(OBJDIR)/$(MAIN).o
	$(CC) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJDIR)/$(MAIN).o: $(MAIN).c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm $(OBJDIR)/*.o $(TARGET)

.PHONY: clean all lib
