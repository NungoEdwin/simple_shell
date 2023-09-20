#include "shell.h"
/**
 * str_tokenizer - splits string into tokens
 * @input_string: pointer to string to tokenize
 * @separator: pointer to delimiters
 * Return: pointer to string of token
 */

char *str_tokenizer(char *input_string, const char *separator)
{
	char *initial, *terminal;
	static char *final;

	initial = (input_string == NULL) ? final : input_string;
	initial += strspn(initial, separator);

	if (*initial == '\0')
	{
		final = NULL;
		return (NULL);
	}

	terminal = initial + strcspn(initial, separator);

	if (*terminal != '\0')
		*terminal++ = '\0';

	final = terminal;
	return (initial);
}
