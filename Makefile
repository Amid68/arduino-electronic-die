# @file Makefile
# @brief Build script for the electronic die project
# @author Ameed Othman
# @date 2024-10-31

CC = avr-gcc
CFLAGS = -Wall -Iinclude

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

APP_SRC = $(wildcard $(SRCDIR)/application/*.c)
DRV_SRC = $(wildcard $(SRCDIR)/drivers/*.c)
SRC = $(APP_SRC) $(DRV_SRC)
OBJS = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TARGET = $(BINDIR)/arduino_electronic_die

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean

