#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>
#include <signal.h>

#define SIZE 100
#define MAX_ARGS 10
#define MAX_LEN  50
#define MAX_CMDS 10
