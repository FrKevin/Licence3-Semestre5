/* mshell - a job manager */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include "cmd.h"
#include "sighandlers.h"
#include "jobs.h"
#include "pipe.h"
#include "common.h"

static char prompt[] = "mshell> ";      /* command line prompt */

/*
 * usage - print a help message
 */
void usage(void) {
    printf("Usage: mshell [-hv]\n");
    printf("   -h   print this message\n");
    printf("   -v   print additional diagnostic information\n");
    exit(EXIT_FAILURE);
}

/*
 * parseline - Parse the command line and build the token array, which
 * contains argv arrays.
 *
 * Return true if the user has requested a BG job, false if
 * the user has requested a FG job.
 */
int parseline(char *cmdline, char *token[MAXCMDS][MAXARGS], int *nbcmd) {
    int i, j, k;

    strtok(cmdline, "|");
    token[0][0] = cmdline;
    i = 1;
    while ((token[i][0] = (char *) strtok(NULL, "|")) != NULL) {
        while (*token[i][0] == ' ')
            token[i][0]++;
        i++;
    }

    for (j = 0; j < i; j++) {
        strtok(token[j][0], " ");
        k = 1;
        while ((token[j][k] = (char *) strtok(NULL, " ")) != NULL) {
            while (*token[j][k] == ' ')
                token[j][k]++;
            k++;
        }
        token[j][k] = NULL;
    }

    *nbcmd = i;

    /* case: cmd & */
    if ((*token[j - 1][k - 1] == '&') != 0) {
        token[j - 1][k - 1] = NULL;
        return 1;
    }
    /* case: cmd&   */
    if ((token[j - 1][k - 1][strlen(token[j - 1][k - 1]) - 1] == '&') != 0) {
        token[j - 1][k - 1][strlen(token[j - 1][k - 1]) - 1] = '\0';
        return 1;
    }

    return 0;                   /* foreground job */
}

/*
 * builtin_cmd - If the user has typed a built-in command then execute
 *    it immediately.
 */
int builtin_cmd(char **argv) {
    char *cmd = argv[0];

    if (!strcmp(cmd, "help")) {
        do_help();
        return 1;
    }

    if (!strcmp(cmd, "stop")) {
        do_stop(argv);
        return 1;
    }

    if (!strcmp(cmd, "exit")) {
        do_exit();
        return 1;
    }

    if (!strcmp(cmd, "jobs")) {
        do_jobs();
        return 1;
    }

    if (!strcmp(cmd, "bg")) {
        do_bg(argv);
        return 1;
    }

    if (!strcmp(cmd, "fg")) {
        do_fg(argv);
        return 1;
    }

    if (!strcmp(cmd, "kill")) {
        do_kill(argv);
        return 1;
    }


    return 0;                   /* not a builtin command */
}

void eval(char *cmdline) {
    char *token[MAXCMDS][MAXARGS];      /* token[i] is a command typed in the command line */
    int nbcmd;                          /* number of commands typed in the command line */
    int bg;                             /* should the job run in bg or fg? */
    pid_t pid;                          /* process id */
    sigset_t mask;                      /* signal mask */
    char **argv;

    /* Parse command line */
    bg = parseline(cmdline, token, &nbcmd);

    if (nbcmd > 1)              /* a command pipeline has been typed in */
        do_pipe(token, nbcmd, bg);
    else {                      /* no pipeline, only one command */
        argv = token[0];
        if (!builtin_cmd(argv)) {
            /*
             * This is a little tricky. Block SIGCHLD, SIGINT, and SIGTSTP
             * signals until we can add the job to the job list. This
             * eliminates some nasty races between adding a job to the job
             * list and the arrival of SIGCHLD, SIGINT, and SIGTSTP signals.
             */

            if (sigemptyset(&mask) < 0)
                unix_error("sigemptyset error");
            if (sigaddset(&mask, SIGCHLD))
                unix_error("sigaddset error");
            if (sigaddset(&mask, SIGINT))
                unix_error("sigaddset error");
            if (sigaddset(&mask, SIGTSTP))
                unix_error("sigaddset error");
            if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0)
                unix_error("sigprocmask error");

            /* Create a child process */
            if ((pid = fork()) < 0)
                unix_error("fork error");

            /*
             * Child  process
             */
            if (pid == 0) {
                /* Child unblocks signals */
                sigprocmask(SIG_UNBLOCK, &mask, NULL);

                /* Each new job must get a new process group ID
                   so that the kernel doesn't send ctrl-c and ctrl-z
                   signals to all of the shell's jobs */
                if (setpgid(0, 0) < 0)
                    unix_error("setpgid error");

                /* Now load and run the program in the new job */
                if (execvp(argv[0], argv) < 0) {
                    printf("%s: Command not found\n", argv[0]);
                    exit(EXIT_FAILURE);
                }
            }

            /*
             * Parent process
             */
            /* Parent adds the job, and then unblocks signals so that
               the signals handlers can run again */
            jobs_addjob(pid, (bg == 1 ? BG : FG), cmdline);
            sigprocmask(SIG_UNBLOCK, &mask, NULL);

            if (!bg)
                waitfg(pid);
            else
                printf("[%d] (%d) %s\n", jobs_pid2jid(pid), (int) pid, cmdline);
        }
    }
    return;
}

/*
 * main - The shell's main routine
 */
int main(int argc, char **argv) {
    char c;
    char cmdline[MAXLINE];

    verbose = 0;

    /* Redirect stderr to stdout (so that driver will get all output
     * on the pipe connected to stdout) */
    dup2(1, 2);

    /* Parse the command line */
    while ((c = getopt(argc, argv, "hv")) != EOF) {
        switch (c) {
        case 'h':              /* print help message */
            usage();
            break;
        case 'v':              /* emit additional diagnostic info */
            verbose = 1;
            break;
        default:
            usage();
        }
    }

    /* Install the signal handlers */

    /* These are the ones you will need to implement */
    sigaction_wrapper(SIGINT, sigint_handler);  /* ctrl-c */
    sigaction_wrapper(SIGTSTP, sigtstp_handler);        /* ctrl-z */
    sigaction_wrapper(SIGCHLD, sigchld_handler);        /* Terminated or stopped child */

    /* Initialize the job list */
    jobs_initjobs();

    printf("\nType help to find out all the available commands in mshell\n\n");

    /* Execute the shell's read/eval loop */
    while (1) {
        /* Read command line */
        printf("%s", prompt);

        if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin)) {
            fprintf(stdout, "fgets error\n");
            exit(EXIT_FAILURE);
        }
        if (feof(stdin)) {      /* End of file (ctrl-d) */
            fflush(stdout);
            exit(EXIT_SUCCESS);
        }

        /* Evaluate the command line */
        if (cmdline[0] != '\n') {   /* evaluate the command line only when not empty */
            cmdline[strlen(cmdline) - 1] = '\0';       /* remove the '\n' at the end */
            eval(cmdline);
            fflush(stdout);
            fflush(stdout);
        }
    }

    exit(EXIT_SUCCESS);         /* control never reaches here */
}
