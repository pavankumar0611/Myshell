#include "defs.h"
#include "decl.h"

void trim_trailing_space(char *s) {
	int  len = strlen(s);
	/* for removing trailing spaces */
	while (len > 0 && isspace((unsigned char)s[len - 1])) {
		s[--len] = '\0';
	}   
}

//Check if the user passed the redirection to a file and save the file name if passed.
int to_check_if_the_string_contains_redirection_to_file (char *original_string , int tocheck_redirection ,char *outfile_name) {

	char *temp_string = original_string;

	int i = 0;
	while(temp_string[i++] != '\0') {

		if(temp_string[i] == '>') {
			tocheck_redirection = 1;
			break;
		}
	}   

	if(tocheck_redirection) {
		strcpy(outfile_name, &temp_string[i+ 2]);

		original_string[i] = '\0';
		return 1;
	}   
	else
		return 0;
}

char *parse_commandline_argument(char *string)
{
	/* skip leading whitespace */
	while (isspace((unsigned char)*string))
		string++;

	/* must start with "cd" */
	if (strncmp(string, "cd", 2) != 0)
		return NULL;

	string += 2;

	/* skip whitespace after cd */
	while (isspace((unsigned char)*string))
		string++;

	return string;
}

//prints the coloured pwd on temrinal
void printPrompt() {
	char cwd[PATH_MAX];
	const char* green = "\033[0;32m";
	const char* reset = "\033[0m";

	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		write(STDOUT_FILENO, green, strlen(green));
		write(STDOUT_FILENO, "pavan:<", 7);
		write(STDOUT_FILENO, cwd, strlen(cwd));
		write(STDOUT_FILENO, ">$", 2);
		write(STDOUT_FILENO, reset, strlen(reset));
	}
}

//Try executing a command by searching through PATH variable
//returns 1 if executed successfully , 0 otherwise
int handle_path_execution(char *string)
{
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
