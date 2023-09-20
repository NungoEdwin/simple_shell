#include "shell.h"
/**
 * _read_lines - reads lines from a file or stdin
 * Return: pointer to lines read as string
 */
char *_read_lines(void)
{
	char *input_commands = NULL;
	size_t buffer_size = 0;

	if (getline(&input_commands, &buffer_size, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(input_commands);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(input_commands);
			perror(shell_name);
			exit(EXIT_FAILURE);
		}
	}
	return (input_commands);

}
