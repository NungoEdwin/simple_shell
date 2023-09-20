#include "shell.h"
/**
 * command_path - gets the full path of command
 * @command: command the
 * Return: string to full path
 */
char *command_path(char *command)
{
	char *full_path, *sys_path, *copy_of_sys_path, *split_path;

	sys_path = getenv("PATH");
	copy_of_sys_path = strdup(sys_path);
	/*  PATH manipulation over here */

	split_path = str_tokenizer(copy_of_sys_path, ":");

	while (split_path != NULL)
	{
		full_path = malloc(sizeof(char) *
				(strlen(split_path) + strlen(command) + 2));
		if (full_path != NULL)
		{
			strcpy(full_path, split_path);
			strcat(full_path, "/");
			strcat(full_path, command);

			if (access(full_path, X_OK) == 0)
			{
				free(copy_of_sys_path);
				return (full_path);
			}
			split_path = str_tokenizer(NULL, ":");
		}

		free(full_path);

	}

		free(copy_of_sys_path);
		free(split_path);

		return (NULL);
}
