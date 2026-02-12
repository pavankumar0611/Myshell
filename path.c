#include "defs.h"

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
