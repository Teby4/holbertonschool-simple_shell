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

int executor(char *realpath, char **array)
{
    pid_t pid;
    int status, exit_status = 0;

    if (realpath == NULL)
        return (exit_status);

    pid = fork();

    if (pid == 0)
    {
        if (execve(realpath, array, environ) == -1)
        {
            perror("Error in execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            exit_status = WEXITSTATUS(status);
        }
    }

    return (exit_status);
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

			free(command);
			path_token = strtok(NULL, ":");
		}
		path++;
	}

	return (command_path);
}

/**
 * executepath - Execute a command using the given command path and arguments.
 *
 * @command_path: The full path to the executable.
 * @array: An array of strings representing the command and its arguments.
 * Return: On success, returns the command_path
 */

int executepath(char *command_path, char **array)
{
	int returnvalue = 0;

	if (array == NULL || array[0] == NULL)
    {
        return (-1);
    }

	if (stat(command_path, &perms) == 0)
	{
		returnvalue = executor(array[0], array);
		return (returnvalue);
	}
	else
	{
		command_path = get_path(array[0]);
		array[0] = command_path;

		if (stat(array[0], &perms) == -1)
			printf("./hsh: 1: %s: not found", array[0]);

		if (stat(array[0], &perms) == 0)
			returnvalue = executor(array[0], array);

		free(command_path);
		return (returnvalue);
	}

	return (-1);
}
