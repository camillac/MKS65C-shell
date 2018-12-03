#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>

char ** parse_args(char * line, char * c);

char * userid();

char* replace_one(char* line, char what, char* with);

char* trim(char* to_trim);

void cd_exit(char ** args);

int redir_sin(char * line);
int redir_sout(char * line);

int pipes(char * line);

int reg(char * line);

int semi_colon(char * line);

void print_prompt();
