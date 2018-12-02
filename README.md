# CAMILLA'S WONDERFUL SHELL
## Features:
* prompt containing username + path in COLOR
* runs basic bash commands (ex. ls, ls -al, cat, etc.)
* cd + exit
* can "cd ~" or "cd" (<- no file path), will cd to home directory
* semi-colon process separation

## Failed/In Progress Features:
* redirection
* pipes

## Bugs and Stuff
* "cd ~" doesn't work for "cd ~/(anything else)"


## Functions:
* **parse_args**
   - arguments:
      - char * line : line of input from the terminal
      - char * c    : the character the line is being separated by
   - return value:
      - char ** - returns string array of each argument in the line
   - what it does:
      - separates each argument in a string and returns all the arguments as a string array
      
* **userid**
   - arguments:
      - n/a
   - return value:
      - char * - returns the user id
   - what it does:
      - gets userid from struct stat and returns it
      
* cd_exit
   - arguments:
      - char ** args : array of arguments in the line
   - return value:
      - void
   - what it does:
      - handles the cd or exit command
