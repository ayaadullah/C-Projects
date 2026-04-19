#include "shell.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

// ════════════════════════════════════════════════════════════════════════════
// Executor
// ════════════════════════════════════════════════════════════════════════════

int Executor::execute(std::vector<Command>& pipeline,
                      EnvManager& env,
                      AliasManager& aliases) {

    if (pipeline.empty()) return 0;

    // Expand $VAR in all args for every command in the pipeline
    for (auto& cmd : pipeline) {
        for (auto& arg : cmd.args) {
            if (!arg.empty() && arg[0] == '$')
                arg = env.expand(arg);
        }
    }

    // ── Single command (no pipe) ─────────────────────────────────────────────
    if (pipeline.size() == 1) {
        Command& cmd = pipeline[0];
        bool bg = cmd.background;

        pid_t pid = fork();
        if (pid == 0) {
            // Child
            if (bg) {
                // Detach from terminal
                setsid();
                int devNull = open("/dev/null", O_RDWR);
                dup2(devNull, STDIN_FILENO);
                close(devNull);
            }
            applyRedirections(cmd, STDIN_FILENO, STDOUT_FILENO);

            // Build argv
            std::vector<const char*> argv;
            for (auto& a : cmd.args) argv.push_back(a.c_str());
            argv.push_back(nullptr);

            execvp(argv[0], const_cast<char* const*>(argv.data()));
            std::cerr << RED << cmd.args[0] << ": command not found" << RESET << "\n";
            _exit(127);
        }

        if (pid < 0) {
            std::cerr << RED << "fork() failed" << RESET << "\n";
            return 1;
        }

        if (bg) {
            std::cout << YELLOW << "[" << pid << "] running in background" << RESET << "\n";
            return 0;
        }

        int status = 0;
        waitpid(pid, &status, 0);
        return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    }

    // ── Pipeline (multiple commands) ─────────────────────────────────────────
    size_t n = pipeline.size();
    std::vector<int[2]> pipes(n - 1);

    // Create all pipes
    for (size_t i = 0; i < n - 1; ++i) {
        if (pipe(pipes[i]) < 0) {
            std::cerr << RED << "pipe() failed" << RESET << "\n";
            return 1;
        }
    }

    std::vector<pid_t> pids(n);

    for (size_t i = 0; i < n; ++i) {
        pids[i] = fork();
        if (pids[i] == 0) {
            // ── Wire up stdin ──
            if (i > 0) dup2(pipes[i - 1][0], STDIN_FILENO);
            // ── Wire up stdout ──
            if (i < n - 1) dup2(pipes[i][1], STDOUT_FILENO);

            // Close all pipe fds in child
            for (size_t j = 0; j < n - 1; ++j) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            // Apply file redirections (overrides pipe wiring if specified)
            applyRedirections(pipeline[i], STDIN_FILENO, STDOUT_FILENO);

            std::vector<const char*> argv;
            for (auto& a : pipeline[i].args) argv.push_back(a.c_str());
            argv.push_back(nullptr);

            execvp(argv[0], const_cast<char* const*>(argv.data()));
            std::cerr << RED << pipeline[i].args[0] << ": command not found" << RESET << "\n";
            _exit(127);
        }
    }

    // Parent: close all pipe fds
    for (size_t j = 0; j < n - 1; ++j) {
        close(pipes[j][0]);
        close(pipes[j][1]);
    }

    // Wait for all children
    int lastStatus = 0;
    for (size_t i = 0; i < n; ++i) {
        int status;
        waitpid(pids[i], &status, 0);
        if (i == n - 1)
            lastStatus = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    }
    return lastStatus;
}

// ── Apply < > >> redirections ────────────────────────────────────────────────
void Executor::applyRedirections(const Command& cmd, int inFd, int outFd) {
    if (!cmd.inputFile.empty()) {
        int fd = open(cmd.inputFile.c_str(), O_RDONLY);
        if (fd < 0) {
            std::cerr << RED << cmd.inputFile << ": no such file" << RESET << "\n";
            _exit(1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    if (!cmd.outputFile.empty()) {
        int flags = O_WRONLY | O_CREAT | (cmd.appendMode ? O_APPEND : O_TRUNC);
        int fd = open(cmd.outputFile.c_str(), flags, 0644);
        if (fd < 0) {
            std::cerr << RED << cmd.outputFile << ": cannot open" << RESET << "\n";
            _exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}
