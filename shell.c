#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

// get trim*


char ** parse_args(char * line){
  char ** array = calloc(5, sizeof(char*));
  char s[100];
  sprintf(s, "%s", line);

  printf("%ld\n", strlen(line));
  char *s1 = strncpy(s1, s, strlen(line) - 1);
  while (*s1){
    printf("[%d,%c] ", *s1, *s1);
    s1++;
  }

  //printf("S1 = '%s'\n", s1);
  int x = 0;

  while ((array[x++] = strsep( &s1, " ")) && s1){
    //for (int n = 0; n < 5; n++){
    //  printf("%x = '%s'\n", n, array[n]);
    //}
    //printf("'%s'\n", s1);
    if (strcmp(s1,"") == 0){
      break;
    }
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
  char * line;
  fgets(line, 100, stdin);
  //printf("LINE: '%s'\n", line);

  char ** args = parse_args( line );
  execvp(args[0], args);

  printf("%s\n", strerror(errno));
  free(args);
  return 0;
}
