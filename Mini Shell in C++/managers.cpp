#include "shell.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

// ════════════════════════════════════════════════════════════════════════════
// EnvManager
// ════════════════════════════════════════════════════════════════════════════

void EnvManager::set(const std::string& key, const std::string& val) {
    vars[key] = val;
    ::setenv(key.c_str(), val.c_str(), 1);   // also set in real environment
}

void EnvManager::unset(const std::string& key) {
    vars.erase(key);
    ::unsetenv(key.c_str());
}

std::string EnvManager::get(const std::string& key) const {
    auto it = vars.find(key);
    if (it != vars.end()) return it->second;
    const char* env = ::getenv(key.c_str());
    return env ? std::string(env) : "";
}

bool EnvManager::has(const std::string& key) const {
    return vars.count(key) || ::getenv(key.c_str());
}

void EnvManager::printAll() const {
    for (auto& [k, v] : vars)
        std::cout << CYAN << k << RESET << "=" << GREEN << v << RESET << "\n";
}

// Expand $VAR tokens inside a string
std::string EnvManager::expand(const std::string& token) const {
    if (token.empty() || token[0] != '$') return token;
    std::string key = token.substr(1);
    return get(key);
}

// ════════════════════════════════════════════════════════════════════════════
// AliasManager
// ════════════════════════════════════════════════════════════════════════════

void AliasManager::add(const std::string& name, const std::string& value) {
    aliases[name] = value;
}

void AliasManager::remove(const std::string& name) {
    aliases.erase(name);
}

std::string AliasManager::resolve(const std::string& name) const {
    auto it = aliases.find(name);
    return (it != aliases.end()) ? it->second : name;
}

bool AliasManager::has(const std::string& name) const {
    return aliases.count(name) > 0;
}

void AliasManager::printAll() const {
    for (auto& [name, val] : aliases)
        std::cout << MAGENTA << "alias " << name << RESET << "='" << val << "'\n";
}

// ════════════════════════════════════════════════════════════════════════════
// HistoryManager
// ════════════════════════════════════════════════════════════════════════════

HistoryManager::HistoryManager(size_t max) : maxSize(max) {}

void HistoryManager::add(const std::string& cmd) {
    if (cmd.empty()) return;
    if (history.size() >= maxSize) history.erase(history.begin());
    history.push_back(cmd);
}

void HistoryManager::print() const {
    for (size_t i = 0; i < history.size(); ++i)
        std::cout << YELLOW << std::setw(4) << (i + 1) << RESET
                  << "  " << history[i] << "\n";
}

const std::vector<std::string>& HistoryManager::getAll() const {
    return history;
}
