#include "defs.h"
#include "decl.h"

int main()
{
	pid_t pid;
	char *args[5], output_file_name[SIZE/2];
	char buffer[SIZE];
	int status, generating_output_to_file ;
	// ANSI escape code for green text
	const char* green = "\033[0;32m";
	// ANSI escape code to reset text color to default
	const char* reset = "\033[0m";

	while(1)
	{
		char string[SIZE];
		generating_output_to_file = 0;

		if(getcwd(buffer, SIZE) != NULL)
			printf("%spavan:<%s>$%s",green ,buffer, reset);

		fgets(string , sizeof(string), stdin);
		string[strcspn(string, "\n")] = '\0';

		generating_output_to_file = to_check_if_the_string_contains_redirection_to_file(string , generating_output_to_file ,output_file_name);
		trim_trailing_space(string);


		int string_contains_pipe = contains_pipe(string);

		if(!string_contains_pipe && string[0] == 'c' && string[1] == 'd' ) {
			char *temp_string = parse_commandline_argument(string);

			struct stat sb;
			trim_trailing_space(temp_string);
			if (stat(temp_string, &sb) !=  0)
				printf("Path is invalid\n");

			chdir(temp_string);
		}
		else if (!string_contains_pipe && access(string , X_OK) != 0) {

			const char *environment_path = getenv("PATH");
			pid_t pid;
			char fullpath_of_directory[SIZE], *temporary_full_path;
			int status;

			for(;*environment_path  != '\0';) {

				different_path_string(&environment_path, fullpath_of_directory, string);

				if(fullpath_of_directory == NULL){
					printf("environment variable is NULL\n");
					exit(1);
				}

				int i = 0;
				temporary_full_path = fullpath_of_directory;

				char *token = strtok(fullpath_of_directory, " ");
				while (token && i < 5) {
					args[i++] = token;
					token = strtok(NULL, " ");
				}
				args[i] = NULL;
				temporary_full_path[strcspn(temporary_full_path, " ")] = '\0';

				if(access(temporary_full_path, X_OK) == 0) {
					status = 1;
					pid = fork();
					if(pid == 0) {
						execv(args[0] , args);
					}
					else if(pid > 0)
						wait(NULL);

					printf("*************ls found at %s****************\n", fullpath_of_directory);
					break;
				}
			}
			if(!status)
				printf("the %s not found\n", string);
		}
		else if ( string_contains_pipe ) {

			char argument[MAX_ARGS][MAX_LEN];
			char *cmds [MAX_CMDS][MAX_ARGS];

			split(string , " ", argument);

			int n_cmds = build_cmds(argument, cmds);
			exec_pipeline(cmds, n_cmds);
		}
		else{
			pid = fork();
			if(pid == 0) {
				args[0] = string;
				args[1] = NULL;

				if(generating_output_to_file) {
					FILE *fp =      freopen( output_file_name, "w" , stdout);
					if(fp == NULL)
						printf("Error generating the output into a file\n");
				}
				execv(args[0] , args);
			}
			else if(pid > 0)
				wait(NULL);
		}
	}
}
