#include "shell.h"
#include <sstream>
#include <glob.h>
#include <stdexcept>

// ════════════════════════════════════════════════════════════════════════════
// Parser — splits a raw input line into a pipeline of Commands
// ════════════════════════════════════════════════════════════════════════════

std::vector<Command> Parser::parseLine(const std::string& line) {
    std::vector<Command> pipeline;
    std::vector<std::string> segments;

    // ── Split on '|' (not inside quotes) ──
    std::string seg;
    bool inQuote = false;
    char quoteChar = 0;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (!inQuote && (c == '\'' || c == '"')) {
            inQuote = true; quoteChar = c;
            seg += c;
        } else if (inQuote && c == quoteChar) {
            inQuote = false;
            seg += c;
        } else if (!inQuote && c == '|') {
            segments.push_back(seg);
            seg.clear();
        } else {
            seg += c;
        }
    }
    segments.push_back(seg);

    for (auto& s : segments) {
        // trim whitespace
        size_t a = s.find_first_not_of(" \t");
        size_t b = s.find_last_not_of(" \t");
        if (a == std::string::npos) continue;
        pipeline.push_back(parseSegment(s.substr(a, b - a + 1)));
    }
    return pipeline;
}

// ── Parse one pipe-segment into a Command ────────────────────────────────────
Command Parser::parseSegment(const std::string& segment) {
    Command cmd;
    auto tokens = tokenize(segment);

    // Check for background '&' as last token
    if (!tokens.empty() && tokens.back() == "&") {
        cmd.background = true;
        tokens.pop_back();
    }

    // Walk tokens, pulling out redirections
    for (size_t i = 0; i < tokens.size(); ++i) {
        const std::string& t = tokens[i];

        if (t == "<") {
            if (i + 1 < tokens.size()) cmd.inputFile = tokens[++i];
        } else if (t == ">") {
            if (i + 1 < tokens.size()) { cmd.outputFile = tokens[++i]; cmd.appendMode = false; }
        } else if (t == ">>") {
            if (i + 1 < tokens.size()) { cmd.outputFile = tokens[++i]; cmd.appendMode = true; }
        } else {
            // Glob expand, then push
            auto expanded = globExpand(t);
            for (auto& e : expanded) cmd.args.push_back(e);
        }
    }
    return cmd;
}

// ── Tokenizer: handles quotes and splits on whitespace ───────────────────────
std::vector<std::string> Parser::tokenize(const std::string& s) {
    std::vector<std::string> tokens;
    std::string cur;
    bool inSingle = false, inDouble = false;

    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];

        if (c == '\'' && !inDouble) {
            inSingle = !inSingle;
        } else if (c == '"' && !inSingle) {
            inDouble = !inDouble;
        } else if ((c == ' ' || c == '\t') && !inSingle && !inDouble) {
            if (!cur.empty()) { tokens.push_back(cur); cur.clear(); }
        } else {
            cur += c;
        }
    }
    if (!cur.empty()) tokens.push_back(cur);
    return tokens;
}

// ── Glob expansion: expands wildcards like *.cpp, file?.txt ─────────────────
std::vector<std::string> Parser::globExpand(const std::string& token) {
    // Only expand if token contains wildcard characters
    if (token.find_first_of("*?[") == std::string::npos)
        return { token };

    glob_t g;
    int ret = glob(token.c_str(), GLOB_TILDE | GLOB_NOCHECK, nullptr, &g);

    std::vector<std::string> result;
    if (ret == 0) {
        for (size_t i = 0; i < g.gl_pathc; ++i)
            result.emplace_back(g.gl_pathv[i]);
    } else {
        result.push_back(token); // no match — return literal
    }
    globfree(&g);
    return result;
}
