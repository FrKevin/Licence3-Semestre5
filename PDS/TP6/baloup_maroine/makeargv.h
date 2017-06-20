/* ------------------------------
   $Id: makeargv.h,v 1.2 2005/03/14 08:50:35 marquet Exp $
   ------------------------------------------------------------

   Cuts command into argv pieces
   From  Robbins & Robbins: Unix Systems Programming

   Philippe Marquet, Mar 2005
   
*/

#ifndef _MAKEARGV_H_
#define _MAKEARGV_H_

extern int makeargv(const char *s, const char *delimiters, char ***argvp);
extern void freeargv(char **argv);

#endif

