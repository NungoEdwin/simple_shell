#include "shell.h"
/**
 * handle_file - handles passed file
 * @file_name: pointer to hold file_name
 * Return: void
 */
void handle_file(char *file_name)
{
	char **parsed_command;
	char file_buffer[MAX_BUFFER_SIZE];
	ssize_t bytes_read;
	int file_handler = open(file_name, O_RDONLY);

	if (file_handler == -1)
	{
		perror("Error opening the file");
		return;
	}
	else
	{

		while ((bytes_read = read(file_handler,
						file_buffer, sizeof(file_buffer))) > 0)
		{

			file_buffer[bytes_read] = '\0';
			if (!is_white_space(file_buffer))
			{
				parsed_command = parse_command_input(file_buffer,
						TOKEN_SEPARATOR);
				execute_command(parsed_command);
				free_command_memory(parsed_command);
			}
		}

		if (bytes_read == -1)
		{
			perror(shell_name);
			close(file_handler);
			return;
		}
	}

	close(file_handler);
}
/**
 * process_file - processes files
 * @file_name: pointer to filename
 * Return:void
 */
void process_file(char *file_name)
{
	char *error_message;
	struct stat file_struct;

	if (access(file_name, F_OK) == -1)
	{
		error_message = malloc(MAX_BUFFER_SIZE * sizeof(char));

		if (error_message == NULL)
		{
			perror(shell_name);
			exit(EXIT_FAILURE);
		}

		snprintf(error_message, MAX_BUFFER_SIZE,
				"%s: 0: Can't open %s\n",
				shell_name, file_name);

		write(STDERR_FILENO, error_message, strlen(error_message));
		free(error_message);
		exit(EXIT_FAILURE);
	}

	if (stat(file_name, &file_struct) == -1)
	{
		perror("Error getting file information");
		exit(EXIT_FAILURE);
	}

	if (file_struct.st_size == 0)
	{
		fprintf(stderr, "File is empty\n");
		exit(EXIT_FAILURE);
	}

	handle_file(file_name);
}
