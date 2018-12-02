# CAMILLA'S WONDERFUL SHELL
## Features:
* prompt contains username + path in color
* runs basic bash commands
* cd + exit

## Failed/In Progress Features:
* redirection
* pipes

## Functions:
* **parse_args**
   - arguments:
      - char * line : line of input from the terminal
      - char * c    : the character the line is being separated by
   - return value:
      - char ** - returns string array of each argument in the line
   - what it does:
      - separates each argument in a string and returns all the arguments as a string array
