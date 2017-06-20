# mshell - a job manager

CC      = gcc
CFLAGS  = -g
CFLAGS += -Wall -Werror -ansi -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
LDFLAGS = -g
SRCS    = common.c sighandlers.c jobs.c cmd.c pipe.c mshell.c
OBJS    = common.o sighandlers.o jobs.o cmd.o pipe.o mshell.o
EXEC    = mshell

# main entries
all: $(EXEC)

mshell: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

# gcc -MM generated dependencies
cmd.o: cmd.c jobs.h common.h
common.o: common.c
jobs.o: jobs.c jobs.h common.h
mshell.o: mshell.c cmd.h sighandlers.h jobs.h common.h
sighandlers.o: sighandlers.c jobs.h common.h sighandlers.h

# misc
.PHONY: clean realclean
clean:
	rm -f $(OBJS) *~

realclean: clean
	rm -f $(EXEC)
