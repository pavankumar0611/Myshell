#include "defs.h"
#include "decl.h"

void custom_signalHandler(int sig) {
	const char msg[] = "\nCaught SIGINT\n";  // add newline at start
	write(STDOUT_FILENO, msg, sizeof(msg) - 1);
	printPrompt();
}

void set_customsignal_mode() {
	signal(SIGINT, custom_signalHandler);
}

void set_signalIgnore_mode() {
	signal(SIGINT, SIG_IGN);
}

void set_signalDefault_mode() {
	signal(SIGINT, SIG_DFL);
}

