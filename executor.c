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

/**
 * get_path - Searches for an executable command in the path
 *
 * Return: full path
 * @command_path: command
 */

char *get_path(char *command_path)
{
	char *path_token, *command, *path, *result;

	if (stat(command_path, &perms) == 0)
		return (command_path);

	path = getenv("PATH");
	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable is not set\n");
		return (NULL);
	}

	while (path != NULL)
	{
		path_token = strtok(NULL, ":");
		path_token = strtok(path, ":");
		while (path_token != NULL)
		{
			command = malloc(strlen(path_token) + strlen(command_path) + 2);
			if (command == NULL)
			{
				fprintf(stderr, "Error: Failed to allocate memory\n");
				return (NULL);
			}
			sprintf(command, "%s/%s", path_token, command_path);

			if (access(command, X_OK) == 0)
			{
			result = strdup(command);
			free(command);
			return (result);
			}
			free(result);
			free(command);
			path_token = strtok(NULL, ":");
		}
		path++;
	}

	return (command_path);
}
