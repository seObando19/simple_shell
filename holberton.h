#ifndef _HOLBERTON_H_
#define _HOLBERTON_H_
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <assert.h>
#include <errno.h>
#include <wait.h>
#define SIZEBUFFER 1024

char *str_concat(char *s1, char *s2);
char *get_value_env(char **envp, char *variable);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
void intHandler(int i);
void prompt(void);
int listenread(char *);
int get_simple_args(int, char **, char *, char **, char **);
int pid_launch(char **, char *, char **);
void _error(void);
long int _strlen(char *);
int args_nval(char **);
char *getpath(char **);
char **setpathparams(char *);
int appenddir(char *);
int _printenv(char **);
#endif
