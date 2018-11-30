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

// separates each argument in a string and returns all the arguments as a string array
char ** parse_args(char * line, char * c){
  char ** array = calloc(100, sizeof(char*));

  int x = 0;

  char * token;
  while (line && x < 100){
    token = strsep(&line, c);
    if (strcmp(token,"")) {
      array[x] = token;
      x++;
    }
  }

  return array;
}


// returns the userid
char * userid(long stuid){
  	return getpwuid(stuid)->pw_name;
}

int redir(char * r, char * file){
  if (strcmp(r, ">"));
  if (strcmp(r, ">>"));
  if (strcmp(r, "2>"));
  if (strcmp(r, "&>"));
  if (strcmp(r, "<"));
  else
    return -1;
}

int main(){
  pid_t parent = getpid();

  char * dirname = ".";
	struct stat * s = malloc(sizeof(struct stat));
	stat(dirname, s);

  while(1) {
    printf("%s$ ", userid(s->st_uid));

    char * line = calloc(100, sizeof(char));
    fgets(line, 100, stdin);
    char * p = strchr(line, '\n');
    if (p) *p = 0;
    //printf("LINE: '%s'\n", line);

    int index = 0;
    char ** argsep = parse_args(line, ";");
    while(argsep[index]) {

      char ** args = parse_args( argsep[index], " ");

      int status;


      // exit
      if (!strcmp(args[0], "exit")){
        printf("logout\n");
        exit(0);
      }

      // cd
      if (!strcmp(args[0], "cd")){
        int n = chdir(args[1]);
        if (n == -1){
          printf("Error: %s\n", strerror(errno) );
        }
      }

      if (strcmp(args[1], ">") == 0){

      }

      pid_t f1 = fork();
      //while (f1 == 0 && strchr())
      // if child of parent
      if (f1 == 0) {
        execvp(args[0], args);
        return 0;
      }
      // if parent
      else {
        // wait until a child process is done
        int cpid = wait(&status);
        int slept = WEXITSTATUS(status);
      }

      free(args);
      index++;
    }
  }
  return 0;
}
