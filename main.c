#include "shell.h"
/**
 * main - main  shell
 * @argc: argument count
 * @argv: string arguments
 * Return: 0 for success
 */
int main(int argc, char *argv[])
{
	shell_name = argv[0] == NULL ? "tsh" : argv[0];

	if (argc == 2)
	{
		process_file(argv[1]);
	}
	else
	{

		if (is_interactive() == 1)
		{
			initiate_interactive();
		}
		else
		{
			initiate_non_interactive();
		}
	}
	return (0);
}
