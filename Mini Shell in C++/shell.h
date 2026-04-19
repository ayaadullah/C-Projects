#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>

// ─── ANSI Colors ─────────────────────────────────────────────────────────────
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define WHITE   "\033[97m"

// ─── Parsed Command ───────────────────────────────────────────────────────────
struct Command {
    std::vector<std::string> args;   // tokenized arguments
    std::string inputFile;           // < redirection
    std::string outputFile;          // > or >> redirection
    bool appendMode  = false;        // >> flag
    bool background  = false;        // & flag
};

// ─── Environment Manager ─────────────────────────────────────────────────────
class EnvManager {
    std::unordered_map<std::string, std::string> vars;
public:
    void   set(const std::string& key, const std::string& val);
    void   unset(const std::string& key);
    std::string get(const std::string& key) const;
    bool   has(const std::string& key) const;
    void   printAll() const;
    std::string expand(const std::string& token) const; // expand $VAR
};

// ─── Alias Manager ───────────────────────────────────────────────────────────
class AliasManager {
    std::unordered_map<std::string, std::string> aliases;
public:
    void add(const std::string& name, const std::string& value);
    void remove(const std::string& name);
    std::string resolve(const std::string& name) const;
    bool has(const std::string& name) const;
    void printAll() const;
};

// ─── History Manager ─────────────────────────────────────────────────────────
class HistoryManager {
    std::vector<std::string> history;
    size_t maxSize;
public:
    explicit HistoryManager(size_t max = 100);
    void add(const std::string& cmd);
    void print() const;
    const std::vector<std::string>& getAll() const;
};

// ─── Parser ──────────────────────────────────────────────────────────────────
class Parser {
public:
    // Split a full line into pipe-separated commands
    static std::vector<Command> parseLine(const std::string& line);
private:
    static Command parseSegment(const std::string& segment);
    static std::vector<std::string> tokenize(const std::string& s);
    static std::vector<std::string> globExpand(const std::string& token);
};

// ─── Executor ────────────────────────────────────────────────────────────────
class Executor {
public:
    // Execute a pipeline of commands; returns last exit status
    static int execute(std::vector<Command>& pipeline,
                       EnvManager& env,
                       AliasManager& aliases);
private:
    static int runSingle(Command& cmd, int inFd, int outFd);
    static void applyRedirections(const Command& cmd, int inFd, int outFd);
};

// ─── Shell ───────────────────────────────────────────────────────────────────
class Shell {
    EnvManager   env;
    AliasManager aliases;
    HistoryManager history;
    bool running = true;
    int  lastStatus = 0;

    // Built-in handlers
    int builtinCd(const Command& cmd);
    int builtinExit(const Command& cmd);
    int builtinHistory(const Command& cmd);
    int builtinExport(const Command& cmd);
    int builtinUnset(const Command& cmd);
    int builtinAlias(const Command& cmd);
    int builtinUnalias(const Command& cmd);
    int builtinHelp(const Command& cmd);

    bool isBuiltin(const std::string& name) const;
    int  runBuiltin(Command& cmd);

    std::string buildPrompt() const;
    void setupReadline();

public:
    Shell();
    void run();
};
