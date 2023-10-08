# Makefile for shared library

CC = gcc
LD = gcc
CPPFLAGS = -DDEBUG=1
CFLAGS =  -fPIC -Wall -Wextra -std=c11 -O -g
LDFLAGS = -shared
RM = rm -f
TARGET_LIB = libmystack.so

SRCS = mystack.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(LD) ${LDFLAGS} -o $@ $^

clean:
	-${RM} ${TARGET_LIB} ${OBJS}
