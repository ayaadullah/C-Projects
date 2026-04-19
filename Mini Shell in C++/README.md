# 🐚 mysh — Mini Unix Shell in C++

> A feature-rich Unix-like shell built in C++ showcasing OOP design, systems programming, and OS concepts.

![C++17](https://img.shields.io/badge/C++-17-00599C?style=flat&logo=c%2B%2B)
![Build](https://img.shields.io/badge/build-passing-brightgreen)
![License](https://img.shields.io/badge/license-MIT-blue)

---

## ✨ Features

| Feature | Description |
|---|---|
| 🔗 **Piping** | Chain commands with `\|` — supports N-deep pipelines |
| 📁 **I/O Redirection** | `>` overwrite, `>>` append, `<` input from file |
| ⚙️ **Background Processes** | Run any command with `&`, shell remains responsive |
| 🌿 **Environment Variables** | `export VAR=val`, `echo $VAR`, `unset VAR` |
| 🔖 **Aliases** | `alias ll='ls -la'` — session-persistent shortcuts |
| 🌐 **Glob Expansion** | `*.cpp`, `file?.txt`, `src/[abc]*` patterns |
| 🔡 **Tab Autocomplete** | Commands + filenames via GNU Readline |
| 📜 **Command History** | Arrow keys + `history` built-in |
| 🎨 **Colored Prompt** | Shows current directory, last exit status |

---

## 🚀 Build & Run

### Prerequisites
```bash
sudo apt install g++ libreadline-dev   # Ubuntu/Debian
sudo dnf install gcc-c++ readline-devel # Fedora
brew install readline                   # macOS
```

### Build
```bash
git clone https://github.com/ayaadullah/mysh.git
cd mysh
make
./mysh
```

---

## 💡 Usage Examples

### Piping
```bash
mysh ❯ ls | grep .cpp
mysh ❯ cat log.txt | grep ERROR | sort | uniq
mysh ❯ ps aux | grep python | awk '{print $2}'
```

### I/O Redirection
```bash
mysh ❯ echo "Hello World" > output.txt      # overwrite
mysh ❯ echo "More text"  >> output.txt      # append
mysh ❯ sort < unsorted.txt                  # input from file
mysh ❯ grep error < log.txt > errors.txt    # both
```

### Background Processes
```bash
mysh ❯ sleep 10 &
[12345] running in background
mysh ❯ # prompt immediately returns
```

### Environment Variables
```bash
mysh ❯ export NAME=Ayaad
mysh ❯ echo $NAME
Ayaad
mysh ❯ export           # list all vars
mysh ❯ unset NAME
```

### Aliases
```bash
mysh ❯ alias ll='ls -la'
mysh ❯ alias gs='git status'
mysh ❯ alias             # list all aliases
mysh ❯ unalias ll
```

### Glob Expansion
```bash
mysh ❯ ls *.cpp
mysh ❯ cat file?.txt
mysh ❯ rm temp_*
```

---

## 🏗️ Project Structure

```
mysh/
├── main.cpp        # Entry point, signal handling
├── shell.h         # All class declarations
├── shell.cpp       # Shell loop, built-ins, readline setup
├── parser.cpp      # Tokenizer, pipe splitter, glob expansion
├── executor.cpp    # fork/exec, pipe wiring, redirection
├── managers.cpp    # EnvManager, AliasManager, HistoryManager
└── Makefile
```

## 🧠 OOP Design

| Class | Responsibility | Pattern |
|---|---|---|
| `Shell` | Main loop, built-ins, prompt | Facade |
| `Parser` | Tokenize, split pipes, expand globs | Strategy |
| `Executor` | fork/exec, pipe/redirection wiring | Command |
| `EnvManager` | Environment variable store | Repository |
| `AliasManager` | Alias resolution | Strategy |
| `HistoryManager` | Session history | Iterator |

---

## 🛠️ Built-in Commands

```
cd [dir]           Change directory (~ goes home)
exit [code]        Exit shell with optional code
history            Show command history
export VAR=value   Set environment variable
unset VAR          Remove environment variable
alias name='cmd'   Create alias
unalias name       Remove alias
help               Show all commands
```

---

## 📌 Roadmap

- [x] v1.0 — Basic execution, cd, exit, history  
- [x] v2.0 — Pipes, Redirection, Background, Env vars, Aliases, Glob, Autocomplete  
- [ ] v2.1 — Persistent history (`~/.mysh_history`), config file (`~/.myshrc`)  
- [ ] v3.0 — Job control (`jobs`, `fg`, `bg`), signal handling, `&&` / `||`  
- [ ] v3.1 — Shell scripting (run `.sh` files)  

---

## 📄 License

MIT © [Ayaad Ullah Baig](https://github.com/ayaadullah)
