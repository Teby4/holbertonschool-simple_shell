#include "main.h"

/**
 * executor - Executes a command in a child process.
 *
 * @realpath: The full path to the executable.
 * @array: An array of strings representing the command and its arguments.
 *
 * Description:
 * This function creates a child process to execute the specified command using
 * the execve system call. It waits for the child process to complete and frees
 * the allocated memory for the command and path.
 *
 */

void executor(char *realpath, char **array)
{
	pid_t pid;
	int status;

	if (realpath == NULL)
		return;

	pid = fork();

	if (pid == 0)
	{
		if (execve(realpath, array, environ) == -1)
		{
			perror("Error in execve");
			free(array);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}
