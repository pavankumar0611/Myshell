#include "defs.h"

//to check if the string contains the pipe
int contains_pipe(char *str) {
	if (strchr ( str , '|') != NULL)
		return 1;
	else
		return 0;
}

void exec_pipeline(char *cmds[MAX_CMDS][MAX_ARGS], int n_cmds) {
	int fd[2];
	int prev_fd = -1; // to keep track of read end of pipe , if true means last output is stored , read from this.

	for (int i = 0; i < n_cmds; i++) {

		if (i < n_cmds - 1)
			pipe(fd);

		int  pid = fork();

		if (pid == 0) { // child

			if (prev_fd != -1) {                     // for the input-redirection
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}

			if (i < n_cmds - 1) {                    //for the output re-direction
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}

			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}

		// parent
		if (prev_fd != -1)
			close(prev_fd);

		if (i < n_cmds - 1) {
			close(fd[1]);
			prev_fd = fd[0];
		}
	}

	for (int i = 0; i < n_cmds; i++)
		wait(NULL);
}
