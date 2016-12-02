CC		= gcc
CFLAGS		= -g -Wall
OUTPUT		= myshell
OBJFILES	= execute.o parser.o redirect.o symbol.o util.o command.o
TARGET		= myshell.c

all: $(OUTPUT)

$(OUTPUT): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $(OBJFILES) $(TARGET)

.c.o:
		 $(CC) $(CFLAGS) -c $<

clean:
		rm -f $(OBJFILES)
		rm -f $(OUTPUT)
