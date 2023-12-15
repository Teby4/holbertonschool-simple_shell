#include "main.h"

/**
 * ctrld - Handles the SIGQUIT signal by printing a newline and exiting
 */

void ctrld(void)
{
	if	(feof(stdin))
	{
		printf("\n");
		exit(EXIT_SUCCESS);
	}
}

/**
 * readcheck - Checks the result of a read operation and handles accordingly.
 * @read: The result of the read operation.
 * @line: The line read from the input.
 *
 * Return: 1 if the loop should continue, 0 if it should break.
 *
 */

int readcheck(ssize_t read, char **line)
{
	char *newline;

	newline = strchr(*line, '\n');
	if (newline != NULL)
	{
		*newline = '\0';
	}

	if (read == -1)
	{
		return (0);
	}
	if (read == 0 || (*line)[0] == '\0')
	{
		free(*line);
		exit(EXIT_SUCCESS);
	}

	return (1);
}

/**
 * exitcheck - Checks for exits and frees before quitting
 * @command_path: The command to check for exit.
 * @array: array to free
 * @line: line to free
 */

void exitcheck(char *command_path, char **array, char *line)
{
	if (command_path == NULL)
		return;

	if (strcmp(command_path, "exit") == 0)
	{
		free(array);
		free(line);
		exit(EXIT_SUCCESS);
	}
}


/**
 * envcheck - Check and print environment variables.
 * @command_path: The command to check for (e.g., "env").
 *
 * Description: if commandpath = env prints env
 *
 * @command_path: The command to check.
 */

int envcheck(char *command_path)
{
	char **envprint = environ;

	if (strcmp(command_path, "env") == 0)
	{
	while(envprint)
	{
		printf("%s\n", *envprint);
		envprint++;
	}
	return (0);
	}
	return (0);
}
