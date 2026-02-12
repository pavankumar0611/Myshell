#include "defs.h"

//pipe.c 
int contains_pipe(char *str);
void exec_pipeline(char *cmds[MAX_CMDS][MAX_ARGS], int n_cmds);
void execute_simple(char *string, int generating_output_to_file, char *output_file_name);
int handle_pipeline(char *string);

//misc.c
char *parse_commandline_argument(char *string);
void trim_trailing_space(char *s);
int to_check_if_the_string_contains_redirection_to_file (char *original_string , int tocheck_redirection ,char *outfile_name);
void signalhandler(int sig);
void printPrompt(void);
int handle_path_execution(char *string);

//path.c
char *different_path_string(const char **string, char *new_appended_path, char *commandline_argument_passed);
int handle_cd(char *string);

//split.c
void split(char *string, const char *delimiter, char args[MAX_ARGS][MAX_LEN]);
int build_cmds(char args[MAX_ARGS][MAX_LEN], char *cmds[MAX_CMDS][MAX_ARGS]);

//signal.c
void signalHandler(int sig);
void set_shell_mode(void);
void set_parent_exec_mode(void);
void set_child_exec_mode(void);
