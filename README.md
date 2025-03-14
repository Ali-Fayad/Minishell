# Minishell 🐚

A lightweight Unix shell built in C as part of the **42 curriculum**. Minishell replicates basic shell functionalities, including command execution, pipelines, redirections, and signal handling.

## Features 🚀

- **Command execution** using `fork` and `execve`
- **Built-in commands**: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`
- **Pipes (****`|`****)** to chain commands
- **Redirections (****`>`****, ****`<`****, ****`>>`****)** for input/output handling
- **Signal handling** (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- **Environment variable management**
- **Error handling and memory management**

## Installation & Usage 💻

### **1. Clone the Repository**

```bash
git clone https://github.com/yourusername/minishell.git
cd minishell
```

### **2. Compile the Shell**

```bash
make
```

### **3. Run Minishell**

```bash
./minishell
```

### **4. Run Minishell With Valgrind**
```bash
make v
```

## How to Use 📌

- Type commands just like in Bash:
  ```sh
  ls -l | grep minishell > output.txt
  echo "Hello, world!"
  export MY_VAR=value
  ```
- Use `Ctrl+D` to exit the shell.

## Built With 🛠️

- **C** (Norminette compliant)
- **POSIX system calls** (`fork`, `execve`, `pipe`, `dup2`, `waitpid`, etc.)
- **GNU Readline** (if used)

## Authors ✨

- [ali_Fayad](https://github.com/Ali-Fayad)

## License 📜

This project is for educational purposes and follows **42 School guidelines**.

---

🚀 **Minishell: Rebuilding the basics of a Unix shell!**


