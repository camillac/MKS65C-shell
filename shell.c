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
char ** parse_args(char * line){
  char ** array = calloc(100, sizeof(char*));

  int x = 0;

  char * token;
  while (line && x < 100){
    token = strsep(&line, " ");
    if (strcmp(token,"")) {
      array[x] = token;
      x++;
    }
  }


  return array;
}

char * userid(long stuid){
  	return getpwuid(stuid)->pw_name;
}

int main(){
  pid_t parent = getpid();

  char * dirname = ".";
  DIR * d = opendir(dirname);
  if (!d) {
    printf("Error: %s\n", strerror(errno) );
    return errno;
  }

	struct dirent * info = readdir(d);

	struct stat * s = malloc(sizeof(struct stat));
	stat(dirname, s);

  while(getpid() == parent) {
    printf("%s$ ", userid(s->st_uid));

    char * line = calloc(100, sizeof(char));
    fgets(line, 100, stdin);
    char * p = strchr(line, '\n');
    if (p) *p = 0;
    //printf("LINE: '%s'\n", line);

    char ** args = parse_args( line );

    int status;
    // printf("'%s'\n", args[0] );
    // printf("%d\n", strcmp(args[0], "exit"));
    if (!strcmp(args[0], "exit")){
      printf("logout\n");

      //kill(getppid(), SIGKILL);
      return 0;
    }
    if (!strcmp(args[0], "cd"));

    pid_t f1 = fork();


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
  }
  return 0;
}
