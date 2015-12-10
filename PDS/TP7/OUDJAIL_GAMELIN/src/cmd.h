/*! \mainpage Project PDS: mshell
 *
 * \section intro_sec Introduction
 *
 * This project was made to the System Programming module taught the semester 5 at FIL in Lille 1. It is a minimalist command-line interpreter working in an environment Linux. It uses library normalized by POSIX.\n
 * It launches and manages several commands
 * We can explore a files system.
 * Moreover, it supports the communication between different processes and manages a part of the signals.
 *
 * \section install_sec How to use ?
 *  Create the application: make \n
 *  Remove obj folder and remove application: make clean\n
 *  Run application: ./mshell\n
 *  Option to execution : -v (verbose) \n
 *
 *  \authors Kevin Gamelin & Veïs Oudjail
 *  \date 2015
 */

/*!
  \file cmd.h
  \brief define all commands
*/
#ifndef _CMD_H_
#define _CMD_H_

/*!
  \fn void waitfg(pid_t pid)
  \brief Wait a foreground job
*/
extern void waitfg(pid_t pid);

/*!
  \fn void do_exit()
  \brief Exit shell
*/
extern void do_exit();

/*!
  \fn void do_jobs()
  \brief Print the job list
*/
extern void do_jobs();

/*!
  \fn void do_help()
  \brief Print the help page
*/
extern void do_help();

/*!
  \fn void do_bg(char **argv)
  \brief Execute the builtin bg command
  \param argv
*/
extern void do_bg(char **argv);

/*!
  \fn void do_fg(char **argv)
  \brief Execute the builtin fg command
  \param argv
*/
extern void do_fg(char **argv);

/*!
  \fn void do_kill(char **argv)
  \brief Execute the builtin kill command
  \param argv
*/
extern void do_kill(char **argv);

/*!
  \fn void do_stop(char **argv)
  \brief Execute the builtin stop command
  \param argv
*/
extern void do_stop(char **argv);

/*!
  \fn void do_cd(char **argv)
  \brief Execute the builtin cd command
  \param argv
*/
extern void do_cd(char **argv);

#endif
