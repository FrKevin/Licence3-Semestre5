/*! \mainpage Projet PDS: mshell
 *
 * \section intro_sec Introduction
 *
 *  Ce projet a était fait dans le cadre du module de Programmation Des Systèmes enseigné au semestre 5 en licence informatique à Lille 1.
 *  C'est un interpréteur de commande minimaliste fonctionnant dans un environnement Linux.
 *  Il utilise pour cela, des librairies normées par POSIX.
 *  Il permet de lancer et de manager plusieurs commandes.
 *  On peut aussi se balader dans un système de fichiers.
 *  De plus, il supporte la communication entre différents processus et gère une partie des signaux.
 *
 * \section install_sec Commandes possibles ?
 *  Construire l'application: make \n
 *  Supprimer le dossier obj: make clean\n
 *  Supprimer le dossier obj et 'application: make realclean\n
 *  Lancer l'application: ./mshell\n
 *  Option d'execution : ./mshell -v (verbose) \n
 *
 *  \authors Kevin Gamelin & Veïs Oudjail
 *  \date 2015
 */

/*!
  \file cmd.h
  \brief Définies toutes les commandes possibles
*/
#ifndef _CMD_H_
#define _CMD_H_

/*!
  \fn void waitfg(pid_t pid)
  \brief attends un job au premier plan
*/
extern void waitfg(pid_t pid);

/*!
  \fn void do_exit()
  \brief quitte le shell
*/
extern void do_exit();

/*!
  \fn void do_jobs()
  \brief affiche la liste des jobs
*/
extern void do_jobs();

/*!
  \fn void do_help()
  \brief affiche la section d'aide
*/
extern void do_help();

/*!
  \fn void do_bg(char **argv)
  \brief execute la commande bg
  \param argv
*/
extern void do_bg(char **argv);

/*!
  \fn void do_fg(char **argv)
  \brief execute la commande fg
  \param argv
*/
extern void do_fg(char **argv);

/*!
  \fn void do_kill(char **argv)
  \brief execute la commande kill
  \param argv
*/
extern void do_kill(char **argv);

/*!
  \fn void do_stop(char **argv)
  \brief execute la commande stop
  \param argv
*/
extern void do_stop(char **argv);

/*!
  \fn void do_cd(char **argv)
  \brief execute la commande cd
  \param argv
*/
extern void do_cd(char **argv);

#endif
