#ifndef _PIPE_H_
#define _PIPE_H_

#include "common.h"

#define READ 0
#define WRITE 1

extern void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg);

#endif
