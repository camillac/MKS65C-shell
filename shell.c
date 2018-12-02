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

// parse_args
//  arguments:
//    char * line : line of input from the terminal
//    char * c    : the character the line is being separated by
//  return value:
//    char ** - returns string array of each argument in the line
//  what it does:
//    separates each argument in a string and returns all the arguments as a string array
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


int num_args(char ** array){
  int counter = 0;
  while (array[counter]){
    counter++;
  }
  return counter;
}


// userid
//  arguments:
//    n/a
//  return value:
//    char * - returns the user id
//  what it does:
//    gets userid from struct stat and returns it
char * userid(){
  char * dirname = ".";
  struct stat * s = malloc(sizeof(struct stat));
  stat(dirname, s);
  char * uid = getpwuid(s->st_uid)->pw_name;
  free(s);
  return uid;
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

// replace_one
//  arguments:
//    char * line : string that contains character you want to change
//    char what   : the character you want to change
//    char * with : the string you want to replace the character with
//  return value:
//    char * - returns the new string
//  what it does:
//    replaces a character in a string with a string
char* replace_one(char* line, char what, char* with) {
    char* out = calloc(sizeof(char), 1000);
    char* part_two = strchr(line, what);
    *part_two = 0;
    part_two++;
    strcat(out, line);
    strcat(out, with);
    strcat(out, part_two);
    printf("%s\n", out);

    int index = 0;
    while (out[index++]);
    char* outout = calloc(sizeof(char), index);
    strcpy(outout, out);

    free(out);

    return outout;
}

// trim
//  arguments:
//    char * to_trim : the string you want to trim
//  return value:
//    char * - returns the new string
//  what it does:
//    trims empty spaces off the edges of a string
char* trim(char* to_trim) {
  char* start = to_trim;
  while (*start == ' ') {
    start++;
  }
  char* end = to_trim;
  while (*end) {
    end++;
  }
  end--;
  while (*end == ' ') {
    *end = 0;
    end--;
  }
  return start;
}

// cd_exit
//  arguments:
//    char ** args : array of arguments in the line
//  return value:
//    void
//  what it does:
//    handles the cd or exit command
void cd_exit(char ** args){
  int n;
  if (!strcmp(args[0], "cd")){
    n = chdir(args[1]);
    if (args[1] == NULL) {
      n = chdir(getenv("HOME"));
    }
    else if (strchr(args[1], '~') != NULL){
      char * home = replace_one(args[1], '~', getenv("HOME"));
      n = chdir(home);
    }
    if (n == -1){
      printf("-bash: cd: %s: %s\n", args[1], strerror(errno) );
    }
  }
  if (!strcmp(args[0], "exit")){
    printf("logout\n");
    exit(0);
  }
}

int reg(char * line){
  char ** args = parse_args( line, " ");
  int status;

  // if cd or exit
  cd_exit(args);

  pid_t f1 = fork();

  // if child
  if (f1 == 0) {
    execvp(args[0], args);
    return 0;
  }
  // if parent
  // wait until a child process is done
  int cpid = wait(&status);


  free(args);
  return 0;
}

int redir_sin(char * line){
  int x = 1;
  char ** sep = parse_args(line, "<");
  int sin = dup(STDIN_FILENO);
  int fd;
  while (sep[x]){
    fd = open(trim(sep[x]), O_CREAT | O_RDONLY);
    int s = dup2(fd, STDIN_FILENO);
    close(fd);
    x++;
  }
  return sin;
}

int redir_sout(char * line){
  int x = 1;
  char ** sep = parse_args(line, ">");
  int sout = dup(STDOUT_FILENO);
  int fd = STDOUT_FILENO;
  int newfd;
  while (sep[x]){
    // printf("HELLLLLLLLLLO");
    newfd = open(trim(sep[x]), O_CREAT | O_WRONLY);
    int s = dup2(newfd, fd);
    close(newfd);
    x++;
  }
  printf("%s\n", sep[0]);
  reg(sep[0]);
  dup2(sout, newfd);
  return sout;
}

int semi_colon(char * line){
  char ** argsep = parse_args(line, ";");
  int index = 0;
  while(argsep[index]) {
      if (strchr(line, '>'))
        redir_sout(line);
      // else if (strchr(line, '<'))
      //   redir_sin(line);
      // else if (strchr(line, '|'))
      //   pip(line);
      else
        reg(line);
      index++;
  }
  return 0;
}

// run
//  arguments:
//    n/a
//  return value:
//    int - returns 0 for successful, -1 for error
//  what it does:
//    runs the whole process
int run(){
  pid_t parent = getpid();
  char * uid = userid();
  // printf("\e[36mWELCOME TO CAMILLA'S TERMINAL <3\n");

  while(1) {
    printf("\e[92m%s:\e[94m%s\e[92m$ ", uid, getcwd(NULL, 256));

    char * line = calloc(100, sizeof(char));
    fgets(line, 100, stdin);
    char * p = strchr(line, '\n');
    if (p) *p = 0;

    if (strchr(line, ';'))
      semi_colon(line);
    else if (strchr(line, '>'))
      redir_sout(line);
    // else if (strchr(line, '<'))
    //   redir_sin(line);
    // else if (strchr(line, '|'))
    //   pip(line);
    else
      reg(line);

    free(line);
  }
  return 0;
}

int main(){
  return run();
}
