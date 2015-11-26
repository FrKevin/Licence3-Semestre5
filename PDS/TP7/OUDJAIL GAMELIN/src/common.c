/* mshell - a job manager */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "common.h"

void unix_error(char *msg) {
    fprintf(stdout, "%s: %s\n", msg, strerror(errno));
    exit(EXIT_FAILURE);
}

void send_verbose_message(const char* message){
  if(verbose){
    printf(ANSI_COLOR_BOLDGREEN "%s"NORM"\n", message);
  }
}
