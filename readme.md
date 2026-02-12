# MyShell

## Description

This program implements a simple Unix-like shell in C.

The shell supports the following operations:

- Execute simple commands
- Execute commands using system PATH
- Built-in `cd` command
- Output redirection (`>`)
- Command pipelines (`|`)
- Process creation using `fork()` and execution using `exec()`

---

## Build Instructions

Compile the program using:

gcc -Wall -Wextra -o myshell myshell.c

This will generate the executable file:

myshell

---

## Run Instructions

./myshell

The shell will display a prompt and wait for user input.

---

## Supported Operations

### Simple Execution

/bin/ls

or

ls

---

### PATH-Based Execution

pwd  
echo Hello  
whoami  

The shell searches for the command inside the system PATH.

---

### Change Directory (Built-in)

cd /home/user

Changes the current working directory of the shell.

---

### Output Redirection

ls > output.txt

Output will be written to output.txt.  
If the file already exists, it will be overwritten.

---

### Pipeline Support

ls | grep .c

ls | grep .c | wc -l

Multiple commands can be connected using `|`.

---

## Example Usage

### Example 1

myshell> pwd  
/home/user  

### Example 2

myshell> ls | grep .c  
file1.c  
file2.c  

### Example 3

myshell> ls > files.txt  

---

## Notes

- Commands must be valid system executables.
- Use proper spacing around `|` for pipelines.
- Output redirection supports only `>` (overwrite mode).
- Background execution (`&`) is not supported.
- Logical operators (`&&`, `||`) are not supported.

---

## Author

Pavan Kohli  
Mini Shell Project  

