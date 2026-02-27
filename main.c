#include "decl.h"
#include "defs.h"

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

	set_customsignal_mode();
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
