#include "decl.h"
#include "defs.h"

//function to redirect output to a file
void execute_simple(char *string, int generating_output_to_file, char *output_file_name)
{
	set_parent_exec_mode();
	pid_t pid = fork();

	if (pid == 0) {

		char *args[2];
		args[0] = string;
		args[1] = NULL;

		if (generating_output_to_file) {
			FILE *fp = freopen(output_file_name, "w", stdout);
			if (fp == NULL)
				printf("Error generating the output into a file\n");
		}

		set_child_exec_mode();
		execv(args[0], args);
	}
	else if (pid > 0) {
		wait(NULL);
		set_shell_mode();
	}
}

//Try executing a command by searching through PATH variable
//returns 1 if executed successfully , 0 otherwise
int handle_path_execution(char *string)
{
	if (access(string, X_OK) == 0) 			//if the string is executable absolute /relative return 
		return 0;

	const char *environment_path = getenv("PATH");		//get the PATH environment variable
	char fullpath_of_directory[SIZE];
	char *temporary_full_path;
	char *args[5];
	int status = 0;

	while (*environment_path != '\0') {

		different_path_string(&environment_path, fullpath_of_directory, string);

		temporary_full_path = fullpath_of_directory;

		int i = 0;
		char *token = strtok(fullpath_of_directory, " ");
		while (token && i < 5) {
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		temporary_full_path[strcspn(temporary_full_path, " ")] = '\0';


		//To check if the executable exists in this PATH directory
		if (access(temporary_full_path, X_OK) == 0) {

			status = 1;
			set_parent_exec_mode();

			pid_t pid = fork();
			if (pid == 0) {
				set_child_exec_mode();
				execv(args[0], args);
			}
			else if (pid > 0) {
				wait(NULL);
				set_shell_mode();
			}

			printf("*************found at %s****************\n",
					temporary_full_path);
			break;
		}
	}

	if (!status)
		printf("the %s not found\n", string);

	return status;
}

//Detects and execute a pipiline command
//example :  ls - l | wc 
int handle_pipeline(char *string)
{
	if (!contains_pipe(string))
		return 0;

	char argument[MAX_ARGS][MAX_LEN];
	char *cmds[MAX_CMDS][MAX_ARGS];

	split(string, " ", argument);		//split string into token 
	int n_cmds = build_cmds(argument, cmds);
	exec_pipeline(cmds, n_cmds);

	return 1;
}


// to handle  change directory command (cd)
int handle_cd(char *string)
{
	// check if the cmd starts with cd
	if (string[0] == 'c' && string[1] == 'd') {

		char *temp_string = parse_commandline_argument(string);
		struct stat sb;

		trim_trailing_space(temp_string);

		if (stat(temp_string, &sb) != 0) {
			printf("Path is invalid\n");
			return 1;
		}

		chdir(temp_string);			//change the current working directory
		return 1;
	}
	return 0;
}


void execute_command(char *string)
{
	char output_file_name[SIZE/2];
	int generating_output_to_file = 0;

	generating_output_to_file =
		to_check_if_the_string_contains_redirection_to_file(
				string, generating_output_to_file, output_file_name);

	trim_trailing_space(string);

	if (handle_cd(string))
		return;

	if (handle_pipeline(string))
		return;

	if (handle_path_execution(string))
		return;

	execute_simple(string, generating_output_to_file, output_file_name);
}

int main () {

	char buffer[SIZE];

	set_shell_mode();
	while (1)
		{

			char string[SIZE];

			if (getcwd(buffer, SIZE) != NULL)
				printPrompt();

			errno = 0;
			if (fgets(string, sizeof(string), stdin) == NULL) {
				if (errno == EINTR) {
					clearerr(stdin);
					continue;
				}
				break;
			}

			string[strcspn(string, "\n")] = '\0';		//remove newline from character

			// to ignore the empty input
			if (string[0] == '\0')
				continue;
			
			//execute command
			execute_command(string);
		}
}
