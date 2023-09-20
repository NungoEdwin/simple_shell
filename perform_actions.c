#include "shell.h"
/**
 * perform_actions - function to execute entered commands
 * @parsed_arguments: parsed inputted arguments
 */
void perform_actions(char **parsed_arguments)
{
	char *full_command_path;

	if (is_path_available(parsed_arguments[0]) == 1)
	{
		do_system_call(parsed_arguments[0], parsed_arguments);
	}
	else
	{
		full_command_path = command_path(parsed_arguments[0]);
		do_system_call(full_command_path, parsed_arguments);
		free(full_command_path);
	}
}

/**
 * do_system_call - fxn to execute entered commands
 * @command: actual command to be executed
 * @parsed_args: parsed inputted arguments
 */
void do_system_call(char *command, char **parsed_args)
{
	pid_t process_id;
	char *imploded_command;

	if (command != NULL)
	{
		process_id = fork();
		if (process_id == 0)
		{
			execve(command, parsed_args, NULL);
			perror(shell_name);
		}
		else if (process_id < 0)
		{
			perror(strcat(shell_name, " :1 : "));
		}
		else
		{
			wait(NULL);
		}
	}
	else
	{
		imploded_command = _implode(parsed_args, " ");
		write_error(imploded_command);
		free(imploded_command);
	}
}

/**
 * is_path_available - checks if supplied command path is available
 * @command_path: command full path
 * Return: int
 */
int is_path_available(char *command_path)
{
	int is_available = 0;

	if (access(command_path, F_OK) == 0 &&
		access(command_path, X_OK) == 0)
	{
		is_available = 1;
	}
	return (is_available);
}

/**
 * write_error - prints error message to stderr
 * @imploded_command: pointer to command as string
 * Return: int
 */
int write_error(char *imploded_command)
{
	char *error_message;

	error_message = malloc(MAX_BUFFER_SIZE * sizeof(char));

	if (error_message == NULL)
	{
		perror(shell_name);
		return (1);
	}

	snprintf(error_message, 1024,
			 "%s: 1: %s: Command not found\n",
			 shell_name, imploded_command);

	write(STDERR_FILENO, error_message, strlen(error_message));
	free(error_message);

	return (0);
}
