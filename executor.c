#include "main.h"

/**
 * executor - Executes a command in a child process.
 *
 * @realpath: The full path to the executable.
 * @array: An array of strings representing the command and its arguments.
 * Return: return
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
			exit(2);
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
	char *path_token, *command, *path, *result, *temp_path;

	path = getenv("PATH");
	if (path == NULL)
	{
		fprintf(stderr, "Error: PATH");
		return (NULL); }

	temp_path = strdup(path);
	if (temp_path != NULL)
	{
		path_token = strtok(temp_path, ":");
		while (path_token != NULL)
		{
			command = malloc(strlen(path_token) + strlen(command_path) + 2);
			if (command == NULL)
			{
				fprintf(stderr, "malloc");
				free(temp_path);
				return (NULL); }
			sprintf(command, "%s/%s", path_token, command_path);

			if (access(command, X_OK) == 0)
			{
				result = strdup(command);
				free(command);
				free(temp_path);
				return (result);
			}
			free(command);
			path_token = strtok(NULL, ":");
		}
	}
	free(temp_path);
	return (strdup(command_path));
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
	char *full_path;
	int turnvalue = 0;
	struct stat perms;

	if (stat(command_path, &perms) == 0)
	{
		turnvalue = executor(array[0], array);
		return (turnvalue);
	}
	else
	{
		full_path = get_path(command_path);

		if (full_path != NULL && stat(full_path, &perms) != -1)
		{
			turnvalue = executor(full_path, array);
		}
		else
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", array[0]);
			turnvalue = 127;
		}

		free(full_path);
	}

	return (turnvalue);
}
