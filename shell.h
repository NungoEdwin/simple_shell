#ifndef SHELL_H
#define SHELL_H

#define TOKEN_BUFFER_SIZE 64
#define MAX_BUFFER_SIZE 1024
#define TOKEN_SEPARATOR " \n\a\t\r"

/* HEADER FILES */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <fcntl.h>

/* PROTOTYPES*/
int is_interactive(void);
void initiate_interactive(void);
void initiate_non_interactive(void);
char **parse_command_input(char *command, char *separator);
void perform_actions(char **parsed_arguments);
char *command_path(char *command);
char *_implode(char **splitted_tokens, char *needle);
void execute_command(char **parsed_command);
char *_read_lines(void);
int is_white_space(char *input_string);
char *str_tokenizer(char *input_string, const char *separator);
int _echo(char **parsed_commands);
int is_path_available(char *command_path);
int write_error(char *imploded_command);
void free_command_memory(char **parsed_command);
void do_system_call(char *command, char **parsed_args);
void handle_file(char *file_name);
void process_file(char *file_name);
/* BUILT_IN_FUNCTIONS */
int shell_exit(char **parsed_commands);
int _env(char **parsed_command);
int _cd(char **parsed_command);

extern char **environ;
char *shell_name;

typedef int (*Command)(char **args);

/**
 * struct built_in - a dog's basic info
 * @name: name of command
 * @command: pointer to command
 */
typedef struct built_in
{
	char *name;
	Command command;
} BuiltIn;
#endif /* SHELL_H */
