#include "shell.h"

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
    // printf("logout\n");
    exit(0);
  }
}

// redir_sin
//  arguments:
//    char * line : line of input
//  return value:
//    int - returns 0 for successful, -1 for error
//  what it does:
//    redirects for "<" symbol
int redir_sin(char * line){
  int x = 1;
  char ** sep = parse_args(line, "<");
  int fd = STDIN_FILENO;
  int newfd = -1;
  while (sep[x]){
    newfd = open(trim(sep[x]), O_RDONLY);
    int s = dup2(newfd, fd);
    if (newfd == -1){
      printf("-bash: %s: %s\n", trim(sep[x]), strerror(errno));
    }
    close(newfd);
    x++;
  }
  return 0;
}

// redir_sout
//  arguments:
//    char * line : line of input
//  return value:
//    int - returns 0 for successful, -1 for error
//  what it does:
//    redirects for ">" symbol
int redir_sout(char * line){
  int x = 1;
  char ** sep = parse_args(line, ">");
  int fd = STDOUT_FILENO;
  int newfd = -1;
  while (sep[x]){
    redir_sin(sep[x]);
    newfd = open(trim(sep[x]), O_CREAT | O_WRONLY);
    int s = dup2(newfd, fd);
    if (newfd == -1){
      printf("error: %s\n", strerror(errno));
    }
    close(newfd);
    x++;
  }
  return 0;
}

// pipes
//  arguments:
//    char * line : line of input
//  return value:
//    int - returns 0 for successful, -1 for error
//  what it does:
//    pipes the stdout of one process to the stdin of another
int pipes(char * line){
  int fds[2];
  pipe(fds);
  char ** sep = parse_args(line, "|");

  char ** args0 = parse_args( sep[0], " ");
  char ** args1 = parse_args( sep[1], " ");

  pid_t f = fork();

  if (f < 0){
    printf("%s: %s\n", args1[0], strerror(errno));
  }
  if (f == 0){
    close(fds[0]);
    dup2(fds[1], STDOUT_FILENO);
    int error = execvp(args0[0], args0);
    if (error == -1)
      printf("%s: %s\n", args0[0], strerror(errno));
  }
  else{
    int cpid = wait(NULL);
    close(fds[1]);
    dup2(fds[0], STDIN_FILENO);
    int error = execvp(args1[0], args1);
    if (error == -1)
      printf("%s: %s\n", args1[0], strerror(errno));
  }
  return 0;
}

// reg
//  arguments:
//    char * line : line of input
//  return value:
//    int - returns 0 for successful, -1 for error
//  what it does:
//    runs the individual processes
int reg(char * line){

  char * copy = calloc(sizeof(char), 100);
  strcat(copy, line);
  char ** args = parse_args( copy, " ");
  if (!strcmp(args[0], "cd") || !strcmp(args[0], "exit")){
    cd_exit(args);
    return 0;
  }
  free(copy);

  pid_t f1 = fork();

  int newfd = -1;
  // if child
  if (f1 == 0) {

    if (strchr(line, '|'))
      pipes(line);
    redir_sout(line);
    redir_sin(line);
    args = parse_args( line, " ");

    int error = execvp(args[0], args);
    if (error == -1)
      printf("%s: %s\n", args[0], strerror(errno));
    exit(0);
  }
  // if parent
  // wait until a child process is done
  int cpid = wait(NULL);

  return 0;
}

// semi_colon
//  arguments:
//    char * line : line of input
//  return value:
//    int - returns 0 for successful, -1 for error
//  what it does:
//    separates processes by semicolons
int semi_colon(char * line){
  char ** argsep = parse_args(line, ";");
  int index = 0;
  while(argsep[index]) {
      reg(argsep[index]);
    index++;
  }
  return 0;
}

void print_prompt(char * uid){
  printf("\e[92m%s:\e[94m%s\e[92m$\e[37m ", uid, getcwd(NULL, 256));
}

// get_line
//  arguments:
//    char * line : string in which to store the input
//  return value:
//    void
//  what it does:
//    gets the input from the terminal and stores it in a string
void get_line(char * line){
  fgets(line, 100, stdin);
  char * p = strchr(line, '\n');
  if (p) *p = 0;
}

// main
//  arguments:
//    n/a
//  return value:
//    int - returns 0 for successful, -1 for error
//  what it does:
//    runs the whole process
int main(){
  printf("\e[36m--- WELCOME TO CAMILLA'S TERMINAL :3 ---\n");
  printf("---    pls dont break anything <3    ---\n");

  char * uid = userid();

  while(1) {
    print_prompt(uid);

    char * line = calloc(100, sizeof(char));
    get_line(line);
    if (strlen(line) > 0){
      if (line[0] == '|' || line[0] == '>' || line[0] == '<' || line[0] == ';') {
	printf("-bash: syntax error near unexpected token `%c'\n", line[0]);
      }
      else if (strchr(line, ';'))
	semi_colon(line);
      else
	reg(line);
    }
    free(line);
  }
  return 0;
}
