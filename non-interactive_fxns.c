#include "shell.h"
/**
 * initiate_non_interactive - startsshell in non_interactive mode
 * Return: void
 */

void initiate_non_interactive(void)
{
	char *command_inputs;
	char **parsed_command;

	while ((command_inputs = _read_lines()) != NULL)
	{
		if (!is_white_space(command_inputs))
		{
		parsed_command = parse_command_input(command_inputs, TOKEN_SEPARATOR);
		execute_command(parsed_command);
		free_command_memory(parsed_command);
		}
		free(command_inputs);
	}

}
