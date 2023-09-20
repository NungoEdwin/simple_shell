#include "shell.h"
/**
 * initiate_interactive -starts shell in interactive mode
 * Return: void always
 */
void initiate_interactive(void)
{
	char *command;
	size_t linecap = 0;
	int shell_status = 1;
	ssize_t getline_result;
	char **parsed_command;

	while (shell_status == 1)
	{
		printf("$ ");

		getline_result = getline(&command, &linecap, stdin);

		if (getline_result == -1)
		{
			free(command);
			shell_status = -1;
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (!is_white_space(command))
			{
				parsed_command = parse_command_input(command, TOKEN_SEPARATOR);
				execute_command(parsed_command);
				free_command_memory(parsed_command);
			}

		}
	}

}
