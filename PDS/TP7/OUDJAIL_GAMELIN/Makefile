# mshell - a job manager
VPATH = src
OBJ = ./obj

TP=7
NOM1=Gamelin
NOM2=Oudjail

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
		 rm -rf $(OBJ)/ || true
		 mkdir $(OBJ)
		 mv -f $(OBJS) $(OBJ)

mshell: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

# gcc -MM generated dependencies
cmd.o: cmd.c jobs.h common.h
common.o: common.c common.h
jobs.o: jobs.c jobs.h common.h
mshell.o: mshell.c cmd.h sighandlers.h jobs.h common.h
sighandlers.o: sighandlers.c jobs.h common.h sighandlers.h

# misc
.PHONY: clean realclean

clean:
	rm -rf $(OBJ) *~

realclean: clean
	rm -f $(EXEC)

archive: clean realclean
	zip -r TP${TP}_${NOM1}_${NOM2}.zip *
