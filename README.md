![enter image description here](https://imgs.search.brave.com/H2TZN8Lm9M-v-BHpagnF5fXKHKTiMlMOvhlGoPZLUvo/rs:fit:860:0:0/g:ce/aHR0cHM6Ly93d3cu/bWVtZWNyZWF0b3Iu/b3JnL3N0YXRpYy9p/bWFnZXMvbWVtZXMv/NTMyMTc4OC5qcGc)

## Simple Shell

A basic implementation of a shell program in C, inspired by the Unix shell. This simple shell reads commands from standard input, executes them in child processes, and waits for their completion.

## Requirements.

- Your Shell should:

- Display a prompt and wait for the user to type a command
- The prompt is displayed again each time a command has been executed
- - If an executable cannot be found, print an error message and display the prompt again
- Handle errors.
- Handle command lines with arguments
- You have to handle the “end of file” condition (Ctrl+D)
- Handle the PATH
- fork must not be called if the command doesn’t exist
- Implement the exit built-in, that exits the shell
- Implement the env built-in, that prints the current environment

## Compilation
```js
$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Valgrind

```js
$ valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes./hsh
```

### flowchart
![Screenshot_2](https://github.com/Teby4/holbertonschool-simple_shell/assets/135641220/dba19108-a386-4653-9179-3d97564d2fc2)

## Author

* Felipe Olivera <a href="https://github.com/Teby4" rel="nofollow"><img align="center" alt="github" src="https://www.vectorlogo.zone/logos/github/github-tile.svg" height="24" /></a>
