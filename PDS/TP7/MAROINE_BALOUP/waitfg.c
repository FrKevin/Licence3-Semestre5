/* waitfg - Block until process pid is no longer the foreground process */
void
waitfg(pid_t pid)
{
   struct job_t *j;
   sigset_t maskchld;
   sigset_t masknormal;
    
   j = jobs_getjobpid(pid);

   if (!j)
      return;
   
   /* maskchld initialization (no signal) */
   sigemptyset(&maskchld);
   /* Adding SIGCHLD signal to maskchld */
   sigaddset(&maskchld, SIGCHLD);
   /* Initialize masknormal with previous blocked signals, then block */
   /* all previous blocked signals and all signals in maskchld signals. */
   /* This call ensures that a SIGCHLD isn't caught by a sighandler */
   sigprocmask(SIG_BLOCK, &maskchld, &masknormal);

   while (j->jb_pid == pid && j->jb_state == FG) {
      /* Wait for a signal which isn't blocked in masknormal set, */
      /* ignoring mask previously sets by sigprocmask calls, */
      /* potentially catching some previous blocked signals */
      /* (i.e. blocked SIGCHLD) */
      sigsuspend(&masknormal);
   }
   
   /* Back to previous blocked signals only */
   sigprocmask(SIG_SETMASK, &masknormal, NULL);
       
   return;
}
