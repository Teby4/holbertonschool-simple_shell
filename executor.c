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
		if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            exit(exit_status);
        }
	}
}

/**
 * get_path - Searches for an executable command in the path
 *
 * Return: full path
 * @command_path: command path
 */

char *get_path(char *command_path)
{
	char *path_token, *command, *path;

	if (stat(command_path, &perms) == 0)
	return (command_path);

	path = getenv("PATH");
	if (path != NULL)
	{
		path_token = strtok(path, ":");
		while (path_token)
		{
			command = malloc(strlen(path_token) + strlen(command_path) + 2);
			sprintf(command, "%s/%s", path_token, command_path);

			if (stat(command, &perms) == 0)
			{
				command_path = command;
				break;
			}

			free(command);
			path_token = strtok(NULL, ":");
		}
	}

	return (command_path);
}
