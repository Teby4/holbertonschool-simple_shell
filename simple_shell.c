#include "main.h"

/**
 * simple_shell - A simple shell implementation that reads commands from
 *                standard input, executes them in child processes, and waits
 *                for the completion of the child processes.
 * Return: Always returns 0.
 */

int simple_shell(void)
{
	char *line = NULL, *token, **array = NULL, *command_path = NULL;
	size_t line_size = 0, i = 0;
	ssize_t read;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			printf("#cisfun$ ");

		ctrld(); /*checks for ctrl + d press*/
		read = getline(&line, &line_size, stdin);
		if (!readcheck(read, &line))
		break;

		array = malloc(sizeof(char *) * 1024);
		token = strtok(line, " \t\n");
		while (token)
		{
			array[i] = token;
			token = strtok(NULL, " \t\n");
			i++;
		}
		array[i] = NULL;
		command_path = array[0];
		exitcheck(command_path, array, line);

		if (*command_path == '/')
		executor(command_path, array);

		i = 0;
	}
	free(line);
	return (0);
}
