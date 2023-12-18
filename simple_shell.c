#include "main.h"

/**
 * simple_shell - A simple shell implementation that reads commands from
 *                standard input, executes them in child processes, and waits
 *                for the completion of the child processes.
 * Return: Always returns 0.
 */

int simple_shell(void)
{
	char *line = NULL, *token, **array = NULL, *command_path;
	size_t line_size = 0, i = 0;
	int turnvalue = 0;
	ssize_t read;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			printf("#cisfun$ ");

		signal(SIGINT, ctrld);
		read = getline(&line, &line_size, stdin);
		if (!readcheck(read, &line))
		break;

		if ((line)[0] != '\0' && (line)[0] != '\n' && (line)[0] != ' ')
		{
		array = malloc(sizeof(char *) * 1024);
		token = strtok(line, " \t\n");
		while (token)
		{
			array[i] = token;
			token = strtok(NULL, " \t\n");
			i++; }
		array[i] = NULL;
		command_path = array[0];
		exitcheck(command_path, array, line);
		envcheck(command_path);

		if (strcmp(command_path, "env") != 0)
		turnvalue = executepath(command_path, array);

		free(array);
		}
		i = 0;
	}

	free(line);
	return (turnvalue);
}
