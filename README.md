# CAMILLA'S WONDERFUL SHELL
## Features:
* prompt containing username + path in COLOR
* runs basic bash commands (ex. ls, ls -al, cat, etc.)
* cd + exit
* can "cd ~" or "cd" (<- no file path), will cd to home directory
* semi-colon process separation
* redirection using "<" and ">" (works with multiple symbols)
* pipes (only 1)

## Failed/In Progress Features:

## Bugs and Stuff
* can not use ">" and "<" for the same process
* can not use redirection and pipes in the same line

## Functions:
* **parse_args** - char ** parse_args(char * line, char * c)
   - arguments:
      - char * line : line of input from the terminal
      - char * c    : the character the line is being separated by
   - return value:
      - char ** - returns string array of each argument in the line
   - what it does:
      - separates each argument in a string and returns all the arguments as a string array
      
* **userid** - char * userid()
   - arguments:
      - n/a
   - return value:
      - char * - returns the user id
   - what it does:
      - gets userid from struct stat and returns it
      
* **replace_one** - char* replace_one(char* line, char what, char* with)
   - arguments:
      - char * line : string that contains character you want to change
      - char what   : the character you want to change
      - char * with : the string you want to replace the character with
   - return value:
      - char * - returns the new string
   - what it does:
      - replaces a character in a string with a string
      
* **trim** - char* trim(char* to_trim)
   - arguments:
      - char * to_trim : the string you want to trim
   - return value:
      - char * - returns the new string
   - what it does:
      - trims empty spaces off the edges of a string
      
* **cd_exit** - void cd_exit(char ** args)
   - arguments:
      - char ** args : array of arguments in the line
   - return value:
      - void
   - what it does:
      - handles the cd or exit command
      
* **redir_sin** - int redir_sin(char * line)
   - arguments:
      - char * line : line of input
   - return value:
      - int - returns 0 for successful, -1 for error
   - what it does:
      - redirects for "<" symbol
      
* **redir_sout** - int redir_sout(char * line)
   - arguments:
      - char * line : line of input
   - return value:
      - int - returns 0 for successful, -1 for error
   - what it does:
      - redirects for ">" symbol
      
* **pipes** - int pipes(char * line)
   - arguments:
      - char * line : line of input
   - return value:
      - int - returns 0 for successful, -1 for error
   - what it does:
      - pipes the stdout of one process to the stdin of another
      
* **reg** - int reg(char * line)
   - arguments:
      - char * line : line of input
   - return value:
      - int - returns 0 for successful, -1 for error
   - what it does:
      - runs the individual processes

* **semi_colon** - int semi_colon(char * line)
   - arguments:
      - char * line : line of input
   - return value:
      - int - returns 0 for successful, -1 for error
   - what it does:
      - separates processes by semicolons

* **get_line** - void get_line(char * line)
   - arguments:
      - char * line : string in which to store the input
   - return value:
      - void
   - what it does:
      - gets the input from the terminal and stores it in a string

* **main**
   - arguments:
      - n/a
   - return value:
      - int - returns 0 for successful, -1 for error
   - what it does:
      - runs the whole process
