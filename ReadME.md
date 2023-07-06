#Minishell Readme

Minishell is a shell program written in C that provides a basic command-line interface with various features. The goal of this project is to create a functional shell program that can interpret and execute user commands, handle redirections, implement pipes, expand environment variables, and support built-in shell commands.

#Getting Started
To get started with Minishell, you can clone the repository from GitHub:

bash
Copy code
git clone https://github.com/NuIled/FINALMinishell.git
Prerequisites
Minishell has the following prerequisites:

#GNU readline library
To install the readline library on Ubuntu, you can use the following command:

bash
Copy code
sudo apt-get install libreadline-dev
Building Minishell
To build Minishell, navigate to the project directory and run the following command:

bash
Copy code
make
This will compile the source files and generate the minishell executable.

#Usage
To run Minishell, use the following command:

bash
Copy code
./minishell
Once the shell is running, you can enter commands and interact with the shell.

#Features
Minishell provides the following features:

Prompt: Minishell displays a prompt to indicate that it's ready to accept user commands.
History: Minishell keeps track of the command history, allowing users to navigate and execute previously entered commands.
Command Execution: The shell searches for and launches the appropriate executable based on the PATH variable or using a relative or absolute path.
Global Variable: Minishell is designed to use only one global variable, ensuring a clean and well-structured codebase.
Quoting: The shell correctly handles single quotes ('), preventing interpretation of metacharacters within the quoted sequence.
Double Quotes: Minishell handles double quotes (") and interprets metacharacters in the quoted sequence except for the dollar sign ($).
Redirection: Minishell supports input and output redirection using the <, >, <<, and >> operators.
Pipes: The shell implements pipes (|) to connect the output of one command as the input to the next command in a pipeline.
Environment Variables: Minishell handles environment variables ($ followed by a sequence of characters) and expands them to their corresponding values.
Exit Status: Minishell expands $? to the exit status of the most recently executed foreground pipeline.
Signal Handling: The shell handles ctrl-C, ctrl-D, and ctrl-\ signals, replicating their behavior in the bash shell.
Built-in Commands: Minishell provides several built-in commands, including echo, cd, pwd, export, unset, env, and exit.
Makefile
The provided Makefile contains the following rules:

$(NAME): Compiles the source files to generate the Minishell executable.
all: Same as $(NAME).
clean: Removes object files generated during compilation.
fclean: Removes the Minishell executable and object files.
re: Executes fclean and then all to rebuild the project.
bonus: Additional rule to handle bonus headers, libraries, or functions (if applicable).
Acknowledgments
This project was developed as part of the curriculum at 1337.
