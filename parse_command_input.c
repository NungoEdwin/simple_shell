#include "shell.h"
/**
 * parse_command_input - separate inputted command into array of strings
 * @command_input: pointer to command string
 * @separator: pointer to delimiter
 * Return: pointer that points to the newly parsed array of strings
 */
char **parse_command_input(char *command_input, char *separator)
{
	int buffer_size = TOKEN_BUFFER_SIZE;
	char *copy_of_comd;
	int index_of_token = 0;
	char **split_tokens = malloc(buffer_size * sizeof(char *));
	char *comd_token;

	copy_of_comd = strdup(command_input);

	if (!split_tokens)
	{
		perror("tsh: Could not allocate memory for tokens \n");
		exit(EXIT_FAILURE);
	}
	comd_token = str_tokenizer(copy_of_comd, separator);
	while (comd_token != NULL)
	{
		split_tokens[index_of_token] = strdup(comd_token);
		index_of_token++;
		if (index_of_token >= buffer_size)
		{
			buffer_size += buffer_size;
			split_tokens = realloc(split_tokens, buffer_size * sizeof(char *));
			if (!split_tokens)
			{
				perror("tsh: Could not re-allocate memory for tokens \n");
				exit(EXIT_FAILURE);
			}
		}
		comd_token = str_tokenizer(NULL, separator);
	}
	split_tokens[index_of_token] = NULL;
	free(copy_of_comd);
	return (split_tokens);
}
