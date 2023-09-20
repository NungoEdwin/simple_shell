#include "shell.h"
/**
 * is_interactive - checks whether shell is in interac.. mode
 * Return: 1 or 0 as int
 */

int is_interactive(void)
{
	return (isatty(STDIN_FILENO));
}
/**
 * execute_command -fxn to execute commands
 * @command:pointer to parsed commands
 * Return: void
 */

void execute_command(char **command)
{
	BuiltIn built_in_functions[4] = {
		{"exit", shell_exit},
		{"env", _env},
		{"cd", _cd},
		{"echo", _echo}
	};
	int built_in_num, is_built_in = 0, counter = 0;

	built_in_num = sizeof(built_in_functions) /
		sizeof(built_in_functions[0]);

	while (counter < built_in_num)
	{
		if (strcmp(command[0],
					built_in_functions[counter].name) == 0)
		{
			is_built_in = 1;
			built_in_functions[counter].command(command);
			break;
		}
		counter++;
	}

	if (is_built_in == 0)
		perform_actions(command);
}
/**
 * is_white_space - checks if
 * str contains only whitespace chars
 * @string:pointer to string to check
 * Return: 1 if whitespace else 0
 */

int is_white_space(char *string)
{
	int is_white = 1, counter = 0;

	while (string[counter])
	{
		if (!isspace(string[counter]))
		{
			is_white = 0;
			break;
		}

		counter++;
	}
	return (is_white);
}
