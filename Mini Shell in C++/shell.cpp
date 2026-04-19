#include "shell.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <algorithm>

// ── Readline autocomplete ────────────────────────────────────────────────────
static char** shellComplete(const char* text, int start, int end);
static char*  commandGenerator(const char* text, int state);

// ════════════════════════════════════════════════════════════════════════════
// Shell Constructor + Setup
// ════════════════════════════════════════════════════════════════════════════

Shell::Shell() {
    // Seed a few useful aliases by default
    aliases.add("ll",  "ls -la");
    aliases.add("la",  "ls -A");
    aliases.add("cls", "clear");
    aliases.add("..",  "cd ..");

    // Seed some env defaults
    char* home = getenv("HOME");
    if (home) env.set("HOME", home);
    char* path = getenv("PATH");
    if (path) env.set("PATH", path);

    setupReadline();
}

void Shell::setupReadline() {
    rl_attempted_completion_function = shellComplete;
    using_history();
}

// ════════════════════════════════════════════════════════════════════════════
// Prompt
// ════════════════════════════════════════════════════════════════════════════

std::string Shell::buildPrompt() const {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    std::string dir(cwd);

    // Shorten home directory to ~
    std::string home = env.get("HOME");
    if (!home.empty() && dir.substr(0, home.size()) == home)
        dir = "~" + dir.substr(home.size());

    std::string status = (lastStatus == 0)
        ? std::string(GREEN) + "❯" + RESET
        : std::string(RED)   + "❯" + RESET;

    return std::string(CYAN) + BOLD + "mysh" + RESET + " "
         + YELLOW + dir + RESET + " " + status + " ";
}

// ════════════════════════════════════════════════════════════════════════════
// Built-in Commands
// ════════════════════════════════════════════════════════════════════════════

bool Shell::isBuiltin(const std::string& name) const {
    static const std::vector<std::string> builtins = {
        "cd", "exit", "quit", "history", "export", "set",
        "unset", "alias", "unalias", "help", "echo"
    };
    return std::find(builtins.begin(), builtins.end(), name) != builtins.end();
}

int Shell::builtinCd(const Command& cmd) {
    std::string target;
    if (cmd.args.size() < 2) {
        target = env.get("HOME");
    } else {
        target = cmd.args[1];
    }
    if (chdir(target.c_str()) != 0) {
        std::cerr << RED << "cd: " << target << ": No such file or directory" << RESET << "\n";
        return 1;
    }
    return 0;
}

int Shell::builtinExit(const Command& cmd) {
    int code = 0;
    if (cmd.args.size() > 1) code = std::stoi(cmd.args[1]);
    std::cout << YELLOW << "\nGoodbye! 👋" << RESET << "\n";
    running = false;
    return code;
}

int Shell::builtinHistory(const Command& cmd) {
    history.print();
    return 0;
}

// export VAR=value  or  set VAR=value
int Shell::builtinExport(const Command& cmd) {
    if (cmd.args.size() == 1) { env.printAll(); return 0; }
    for (size_t i = 1; i < cmd.args.size(); ++i) {
        auto& token = cmd.args[i];
        size_t eq = token.find('=');
        if (eq == std::string::npos) {
            std::cerr << RED << "Usage: export VAR=value" << RESET << "\n";
            return 1;
        }
        env.set(token.substr(0, eq), token.substr(eq + 1));
    }
    return 0;
}

int Shell::builtinUnset(const Command& cmd) {
    if (cmd.args.size() < 2) {
        std::cerr << RED << "Usage: unset VAR" << RESET << "\n"; return 1;
    }
    env.unset(cmd.args[1]);
    return 0;
}

// alias name='value'  or  alias (list all)
int Shell::builtinAlias(const Command& cmd) {
    if (cmd.args.size() == 1) { aliases.printAll(); return 0; }

    std::string token = cmd.args[1];
    size_t eq = token.find('=');
    if (eq == std::string::npos) {
        std::cerr << RED << "Usage: alias name='value'" << RESET << "\n"; return 1;
    }
    std::string name  = token.substr(0, eq);
    std::string value = token.substr(eq + 1);
    // Strip surrounding quotes
    if (value.size() >= 2 &&
        ((value.front() == '\'' && value.back() == '\'') ||
         (value.front() == '"'  && value.back() == '"'))) {
        value = value.substr(1, value.size() - 2);
    }
    aliases.add(name, value);
    std::cout << GREEN << "alias " << name << "='" << value << "' added" << RESET << "\n";
    return 0;
}

int Shell::builtinUnalias(const Command& cmd) {
    if (cmd.args.size() < 2) {
        std::cerr << RED << "Usage: unalias name" << RESET << "\n"; return 1;
    }
    aliases.remove(cmd.args[1]);
    return 0;
}

int Shell::builtinHelp(const Command&) {
    std::cout << BOLD << CYAN << "\n  mysh — Mini Unix Shell\n" << RESET;
    std::cout << "  ─────────────────────────────────────────\n";
    std::cout << GREEN << "  Built-ins:\n" << RESET;
    std::cout << "    cd [dir]           Change directory\n";
    std::cout << "    exit [code]        Exit shell\n";
    std::cout << "    history            Show command history\n";
    std::cout << "    export VAR=value   Set environment variable\n";
    std::cout << "    set VAR=value      Alias for export\n";
    std::cout << "    unset VAR          Remove environment variable\n";
    std::cout << "    alias name='cmd'   Create alias\n";
    std::cout << "    unalias name       Remove alias\n";
    std::cout << "    help               Show this help\n";
    std::cout << "\n" << YELLOW << "  Features:\n" << RESET;
    std::cout << "    cmd1 | cmd2        Pipe output\n";
    std::cout << "    cmd > file         Redirect output (overwrite)\n";
    std::cout << "    cmd >> file        Redirect output (append)\n";
    std::cout << "    cmd < file         Redirect input\n";
    std::cout << "    cmd &              Run in background\n";
    std::cout << "    *.cpp, file?.txt   Glob expansion\n";
    std::cout << "    $VAR               Variable expansion\n";
    std::cout << "    Tab                Autocomplete\n\n";
    return 0;
}

int Shell::runBuiltin(Command& cmd) {
    if (cmd.args.empty()) return 0;
    const std::string& name = cmd.args[0];

    if (name == "cd")                      return builtinCd(cmd);
    if (name == "exit" || name == "quit")  return builtinExit(cmd);
    if (name == "history")                 return builtinHistory(cmd);
    if (name == "export" || name == "set") return builtinExport(cmd);
    if (name == "unset")                   return builtinUnset(cmd);
    if (name == "alias")                   return builtinAlias(cmd);
    if (name == "unalias")                 return builtinUnalias(cmd);
    if (name == "help")                    return builtinHelp(cmd);
    return 0;
}

// ════════════════════════════════════════════════════════════════════════════
// Main Loop
// ════════════════════════════════════════════════════════════════════════════

void Shell::run() {
    std::cout << BOLD << CYAN
              << "  ╔══════════════════════════════╗\n"
              << "  ║       mysh  v2.0             ║\n"
              << "  ║  Mini Unix Shell in C++      ║\n"
              << "  ╚══════════════════════════════╝\n"
              << RESET << "  Type " << YELLOW << "help" << RESET << " to see commands.\n\n";

    while (running) {
        // Reap zombie background processes silently
        while (waitpid(-1, nullptr, WNOHANG) > 0);

        std::string prompt = buildPrompt();
        char* rawLine = readline(prompt.c_str());

        if (!rawLine) { // EOF (Ctrl+D)
            std::cout << "\n";
            break;
        }

        std::string line(rawLine);
        free(rawLine);

        // Skip blank lines
        if (line.find_first_not_of(" \t") == std::string::npos) continue;

        // Add to readline's own history (arrow key recall)
        add_history(line.c_str());
        history.add(line);

        // ── Alias resolution on first token ──────────────────────────────────
        // Quick pre-check: replace first word if it's an alias
        {
            std::istringstream ss(line);
            std::string first; ss >> first;
            if (aliases.has(first)) {
                std::string rest;
                std::getline(ss, rest);
                line = aliases.resolve(first) + rest;
            }
        }

        // ── Parse + execute ───────────────────────────────────────────────────
        auto pipeline = Parser::parseLine(line);
        if (pipeline.empty()) continue;

        // Built-in check — only for single-command (no pipe), first command
        if (pipeline.size() == 1 && isBuiltin(pipeline[0].args[0])) {
            lastStatus = runBuiltin(pipeline[0]);
        } else {
            lastStatus = Executor::execute(pipeline, env, aliases);
        }
    }
}

// ════════════════════════════════════════════════════════════════════════════
// Readline Autocomplete
// ════════════════════════════════════════════════════════════════════════════

static const std::vector<std::string> BUILTINS = {
    "cd", "exit", "quit", "history", "export", "set",
    "unset", "alias", "unalias", "help", "clear", "ls", "cat",
    "echo", "grep", "pwd", "mkdir", "rm", "cp", "mv", "touch"
};

static char* commandGenerator(const char* text, int state) {
    static size_t idx;
    static std::string prefix;
    if (state == 0) { idx = 0; prefix = text; }
    while (idx < BUILTINS.size()) {
        const std::string& cmd = BUILTINS[idx++];
        if (cmd.substr(0, prefix.size()) == prefix)
            return strdup(cmd.c_str());
    }
    return nullptr;
}

static char** shellComplete(const char* text, int start, int end) {
    rl_attempted_completion_over = 1;
    if (start == 0) {
        // Completing the command name
        return rl_completion_matches(text, commandGenerator);
    }
    // Completing arguments — fall back to filename completion
    return rl_completion_matches(text, rl_filename_completion_function);
}
