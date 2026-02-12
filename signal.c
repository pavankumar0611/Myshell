#include "defs.h"
#include "decl.h"

void signalHandler(int sig) {
    const char msg[] = "\nCaught SIGINT\n";  // add newline at start
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
	printPrompt();
}

void set_shell_mode() {
    signal(SIGINT, signalHandler);
}

void set_parent_exec_mode() {
    signal(SIGINT, SIG_IGN);
}

void set_child_exec_mode() {
    signal(SIGINT, SIG_DFL);
}

