#include "shell.h"
/**
 * _implode - implodes array of string into one string
 * @splitted_tokens: pointer to array of  tokens
 * @needle: pointer to needle
 * Return: pointer to imploded string
 */


char *_implode(char **splitted_tokens, char *needle)
{
	char *imploded_string = malloc(0);
	int splitted_tkn_index = 0, byteSize = 0;

	while (splitted_tokens[splitted_tkn_index] != NULL)
	{
		byteSize = strlen(splitted_tokens[splitted_tkn_index])
			+ 1 + strlen(needle) + 1;
		imploded_string = realloc(imploded_string, byteSize);
		if (splitted_tkn_index > 0)
		{
			strcat(imploded_string, needle);
		}

		strcat(imploded_string, splitted_tokens[splitted_tkn_index]);
		splitted_tkn_index++;
	}
	return (imploded_string);
}
