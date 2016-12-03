AR = ar
CC = gcc
CFLAGS = -g -Wall
MYSHELL = libmyfuncs.a
OBJFILES = command.o parser.o execute.o util.o symbol.o redirect.o
OUTPUT = MYSHELL
.SUFFIXES : .o .c

$(MYSHELL) : $(OBJFILES)
        $(AR) rv $(MYSHELL) $(OBJFILES)

.c.o :
        $(CC) $(CFLAGS) -c $< -o $@
clean :
        rm -f $(OBJFILES) $(MYSHELL)

