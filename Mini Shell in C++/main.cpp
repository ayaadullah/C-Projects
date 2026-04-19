#include "shell.h"
#include <csignal>
#include <iostream>

// Ignore Ctrl+C in the shell itself (children handle it normally)
static void sigintHandler(int) {
    std::cout << "\n";
    // Re-display prompt — readline handles this automatically
}

int main() {
    signal(SIGINT,  sigintHandler);
    signal(SIGTSTP, SIG_IGN);   // Ignore Ctrl+Z in shell
    signal(SIGQUIT, SIG_IGN);

    Shell shell;
    shell.run();
    return 0;
}
