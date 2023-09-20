#include "shell.h"
/**
 * shell_exit - fxn to for in-built exit
 * @parsed_commands: command to execute
 * Return: int
 */
int shell_exit(char **parsed_commands)
{
	int exit_status;
	char *error_message;

	if (parsed_commands[1])
	{
		exit(atoi(parsed_commands[1]));
		return (atoi(parsed_commands[1]));
		exit_status = atoi(parsed_commands[1]);
		if (exit_status < 0)
		{
			error_message = malloc(MAX_BUFFER_SIZE * sizeof(char));

			if (error_message == NULL)
			{
				perror(shell_name);
				return (1);
			}

			snprintf(error_message, 1024,
					"%s: 1: %s: Illegal number: %d\n",
					shell_name, "exit", exit_status);

			write(STDERR_FILENO, error_message, strlen(error_message));
			free(error_message);
		}
		else
			exit(exit_status);
		return (exit_status);
	}
	else
	{
		exit(0);
		return (0);
	}
}

/**
 * _env - fxn to for in-built env
 * @parsed_commands: command to execute
 * Return: int
 */
int _env(char **parsed_commands __attribute__((unused)))
{
	int counter = 0;

	while (environ[counter] != NULL)
	{
		printf("%s\n", environ[counter]);
		counter++;
	}

	return (counter);
}

/**
 * _cd - function to implement in-built cd
 * @parsed_commands: parsed command to execute
 * Return: int
 */
int _cd(char **parsed_commands __attribute__((unused)))
{
	char previous_dir[1024];

	getcwd(previous_dir, sizeof(previous_dir));

	if (parsed_commands[1] == NULL)
	{
		parsed_commands[1] = getenv("HOME");
	}
	else if (strcmp(parsed_commands[1], "-") == 0)
	{
		parsed_commands[1] = getenv("OLDPWD");
		if (parsed_commands[1] == NULL)
		{
			perror(shell_name);
			return (1);
		}
	}

	if (chdir(parsed_commands[1]) != 0)
	{
		perror(shell_name);
	}
	else
	{
		setenv("OLDPWD", previous_dir, 1);
		setenv("PWD", parsed_commands[1], 1);
	}
	return (0);
}

/**
 * _echo - fxn to implement in-built echo
 * @parsed_commands:  command to execute
 * Return: int
 */
int _echo(char **parsed_commands)
{
	int process_id;

	if (parsed_commands[2])
		write(2, "Too many arguments\n", 20);
	else
	{
		if (strcmp("$$", parsed_commands[1]) == 0)
		{
			process_id = getpid();
			printf("%i\n", process_id);
		}
		else if (strcmp("$?", parsed_commands[1]) == 0)
		{
			int exit_status;

			wait(&exit_status);

			printf("%d", exit_status);
		}
		else
		{
			printf("%s\n", parsed_commands[1]);
		}
	}

	return (0);
}
