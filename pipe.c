#include "defs.h"
#include "decl.h"

//to check if the string contains the pipe
int contains_pipe(char *str) {
	if (strchr ( str , '|') != NULL)
		return 1;
	else
		return 0;
}

// cmds: 2D array where each row is a command (argv-style array)
// n_cmds: number of commands in the pipeline
void exec_pipeline(char *cmds[MAX_CMDS][MAX_ARGS], int n_cmds) {
	int fd[2];
	int prev_fd = -1; // to keep track of read end of pipe , if true means last output is stored , read from this.

	for (int i = 0; i < n_cmds; i++) {

		if (i < n_cmds - 1)
			pipe(fd);

		set_parent_exec_mode();
		int  pid = fork();

		if (pid == 0) { // child
			set_child_exec_mode();

			if (prev_fd != -1) {                     // if there is a input coming form a previous pipe
				dup2(prev_fd, STDIN_FILENO);		//redirect it to stdin
				close(prev_fd);
			}

			if (i < n_cmds - 1) {                    //if this is not the last command,
				dup2(fd[1], STDOUT_FILENO);			// redirect stdout to the write end of current pipe
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

	for (int i = 0; i < n_cmds; i++) {
		wait(NULL);
		set_shell_mode();
	}
}
