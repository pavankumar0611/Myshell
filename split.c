#include "defs.h"

//Splits the input string into tokens based on the given delimiter
// Each token is stored in the args array
void split(char *string, const char *delimiter, char args[MAX_ARGS][MAX_LEN]) {
	int i = 0;
	char *token = strtok(string, delimiter);

	while (token != NULL && i < MAX_ARGS) {
		strncpy(args[i], token, MAX_LEN - 1);
		args[i][MAX_LEN - 1] = '\0';
		i++;
		token = strtok(NULL, delimiter); // to get the next token from the string
	}

	// mark end
	if (i < MAX_ARGS)
		args[i][0] = '\0';
}

// split string into individual elements of the array
// ex : ls -l | wc   i.e ->   [0]= ls , [1] = -l , [2] = | , [3] = wc;
int build_cmds(char args[MAX_ARGS][MAX_LEN],
		char *cmds[MAX_CMDS][MAX_ARGS]) {
	int cmd = 0, arg = 0;

	for (int i = 0; args[i][0] != '\0'; i++) {
		if (strcmp(args[i], "|") == 0) {
			cmds[cmd][arg] = NULL;
			cmd++;
			arg = 0;
		} else {
			cmds[cmd][arg++] = args[i];
		}
	}

	cmds[cmd][arg] = NULL;
	return cmd + 1;
}
