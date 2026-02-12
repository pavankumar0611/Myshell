#include "defs.h"
#include "decl.h"

//For the given shell exectuable commands check in path environment variable
//appended to absolute path save in new_appended_path
char *different_path_string(const char **string, char *new_appended_path, char *commandline_argument_passed)
{
	int  i = 0;
	while(**string  != '\0' && **string != ':') {
		new_appended_path[i++] = *(*string)++;
	}   
	new_appended_path[i++] = '/';

	while( *commandline_argument_passed != '\0') {
		new_appended_path[i++] = *commandline_argument_passed;
		commandline_argument_passed++;
	}   
	new_appended_path[i] = '\0';

	if(**string == ':')
		(*string)++;

	return new_appended_path;
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
