#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

char ** parse_args(char * line){
  char ** array = calloc(5, sizeof(char*));
  char s[100];
  sprintf(s, "%s", line);
  char *s1 = s;
  int x = 0;
  while (s1){
    array[x] = strsep( &s1, " ");
    printf("%s", array[x]);
    x++;
  }

  return array;
}

int main(){
  // char * s;
  // fgets( s, 256, stdin);
  // int cpid;
  // char ** args;
  // pid_t f1 = fork();
  // if (f1 > 0 && s != NULL){
  //   printf("PARENT\n");
  //   cpid = wait(NULL);
  // }
  // else {
  //   printf("CHILD\n");
  //   args = parse_args(s);
  //   printf("args: %s\n", args[0]);
  //   execvp(args[0], args);
  //   printf("NYEH\n");
  //   return 0;
  // }
  // return 0;

  char * line = "ls ";
  // fgets(line, sizeof(char) *100, stdin);
  // printf("LINE: '%s'\n", line);
  char ** args = parse_args( line );
  execvp(args[0], args);
  printf("%s\n", strerror(errno));
  free(args);
  return 0;
}
