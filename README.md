# <p align="center"><strong>Minishell</strong></p>

<p align="center">
  <img src="shell_0.jpeg" alt="minishell" style="width:40%; margin:auto;" />
</p>

| Category            | Details                                                                 |
|---------------------|-------------------------------------------------------------------------|
| Program Name        | minishell                                                              |
| Files to Submit     | Makefile, *.h, *.c                                                     |
| Makefile Rules      | NAME, all, clean, fclean, re                                            |
| Compiler Flags      | -Wall -Wextra -Werror                                                   |
| Allowed Functions | readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history,<br>printf, malloc, free, write, access, open, read, close, fork, wait, waitpid,<br>wait3, wait4, signal, sigaction, kill, exit, getcwd, chdir, stat, lstat,<br>fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir,<br>strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr,<br>tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs                                                                                                                                 |
| Libft Allowed       | Yes                                                                    |
| Description         | Write a shell                                               |

# General Instructions
• The project must be written in **C** following the Norm. Any norm violation will result in a score of 0.  
• Robust memory management:  
  - No leaks (except known leaks from readline)  
  - No crashes (segfault, bus error, double free, etc.)  
• **Required Makefile** with:  
  - Rules: `$(NAME)`, `all`, `clean`, `fclean`, `re`  
  - Compiler flags: `-Wall -Werror -Wextra`  
  - No unnecessary relinking  
• For bonus:  
  - A separate `bonus` rule in the Makefile  
  - Bonus code must be in files named `*_bonus.c`/`*_bonus.h`  
• If using libft:  
  - Include it in the `libft/` directory with its own Makefile  
  - Compile libft first  
• Submission must be via the assigned Git repository

# Mandatory Part
## Technical Description
The minishell must implement:

### Basic Features
• An interactive prompt with history  
• Searching for executables using PATH or via relative/absolute paths  
• Handling a single global variable exclusively for signals

### Command Processing
• Quote handling:  
  - `'...'` (no interpretation)  
  - `"..."` (with expansion of `$`)  
• Redirections:  
  - `<`, `>`, `<<` (here-doc), `>>` (append)  
• Pipes (`|`) between commands  
• Environment variables:  
  - Expansion of `$VAR` and `$?`  
  - Builtins: `export`, `unset`, `env`, `echo`, `cd`, `pwd`, `exit`

### Signals
• Bash-like behavior for:  
  - Ctrl+C (prints a new line with a fresh prompt)  
  - Ctrl+D (exits the shell)  
  - Ctrl+\ (no action)

### Mandatory Builtins
• `echo` with the `-n` option  
• `cd`   
• `pwd`  
• `exit`  
• `env`    
• `export`  
• `unset`  
### Attachments

Please download the attachments below:<br>
[subject.pdf](./minishell.pdf)

# <p align="center"><strong>Minishell Eval</strong></p>

# __**MANDATORY PART**__

## **Simple Command & global variables**

Execute a simple command with an absolute path like /bin/ls, or any other command without any options.

How many global variables are used? Why? Ask the evaluated student to give you a concrete example of why it feels mandatory or logical.

Check the global variable. This global variable cannot provide any other information or data access than the number of a received signal.

Test an empty command.

Test only spaces or tabs.

If something crashes, select the "crash" flag.

If something doesn't work, select the "incomplete work" flag.

[**YES**](#)  |  [**NO**](#)


## **Redirection**

Execute commands with redirections < and/or >

Repeat multiple times with different commands and arguments and sometimes change > with >>

Check if multiple tries of the same redirections fail.

Test << redirection (it doesn't have to update the history).

[**YES**](#)  |  [**NO**](#)


## **env**

Check if env shows you the current environment variables.

[**YES**](#)  |  [**NO**](#)


## **export**

Export environment variables, create new ones and replace old ones.

Check the result with env.

[**YES**](#)  |  [**NO**](#)


## **echo**

Execute the echo command with or without arguments, or the -n option.

Repeat multiple times with different arguments.

If something crashes, select the "crash" flag.

If something doesn't work, select the "incomplete work" flag.

[**YES**](#)  |  [**NO**](#)


## **Compile**

Use "make -n" to see if compilation use "-Wall -Wextra -Werror". If not, select the "invalid compilation" flag.

minishell compiles without any errors. If not, select the flag.

The Makefile must not re-link. If not, select the flag.

[**YES**](#)  |  [**NO**](#)


## **Arguments**

Execute a simple command with an absolute path like /bin/ls, or any other command with arguments but without any quotes or double quotes.

Repeat multiple times with different commands and arguments.

If something crashes, select the "crash" flag.

If something doesn't work, select the "incomplete work" flag.

[**YES**](#)  |  [**NO**](#)


## **Environment path**

Execute commands but this time without any path (ls, wc, awk and so forth).

Unset the $PATH and ensure commands are not working anymore.

Set the $PATH to a multiple directory value (directory1:directory2) and ensure that directories are checked in order from left to right.

[**YES**](#)  |  [**NO**](#)


## **Go Crazy and history**

Type a command line, then use ctrl-C and press "Enter". The buffer should be clean and there should be nothing left to execute.

Can we navigate through history using Up and Down? Can we retry some command?

Execute commands that should not work like 'dsbksdgbksdghsd'. Ensure minishell doesn't crash and prints an error.

'cat | cat | ls' should behave in a "normal way".

Try to execute a long command with a ton of arguments.

Have fun with that beautiful minishell and enjoy it!

[**YES**](#)  |  [**NO**](#)


## **exit**

Execute exit command with or without arguments.

Repeat multiple times with different arguments.

Don't forget to relaunch the minishell

If something crashes, select the "crash" flag.

If something doesn't work, select the "incomplete work" flag.

[**YES**](#)  |  [**NO**](#)


## **Pipes**

Execute commands with pipes like 'cat file | grep bla | more'

Repeat multiple times with different commands and arguments.

Try some wrong commands like 'ls filethatdoesntexist | grep bla | more'

Try to mix pipes and redirections.

[**YES**](#)  |  [**NO**](#)


## **Signals**

ctrl-C in an empty prompt should display a new line with a new prompt.

ctrl-\ in an empty prompt should not do anything.

ctrl-D in an empty prompt should quit minishell --> RELAUNCH!

ctrl-C in a prompt after you wrote some stuff should display a new line with a new prompt.

The buffer should be clean too. Press "Enter" to make sure nothing from the previous line is executed.

ctrl-D in a prompt after you wrote some stuff should not do anything.

ctrl-\ in a prompt after you wrote some stuff should not do anything.

Try ctrl-C after running a blocking command like cat without arguments or grep "something".

Try ctrl-\ after running a blocking command like cat without arguments or grep "something".

Try ctrl-D after running a blocking command like cat without arguments or grep "something".

Repeat multiple times using different commands.

If something crashes, select the "crash" flag.

If something doesn't work, select the "incomplete work" flag.

[**YES**](#)  |  [**NO**](#)


## **Single Quotes**

Execute commands with single quotes as arguments.

Try empty arguments.

Try environment variables, whitespaces, pipes, redirection in the single quotes.

echo '$USER' must print "$USER".

Nothing should be interpreted.

[**YES**](#)  |  [**NO**](#)


## **pwd**

Use the command pwd.

Repeat multiple times in different directories.

[**YES**](#)  |  [**NO**](#)


## **Double Quotes**

Execute a simple command with arguments and, this time, use also double quotes (you should try to include whitespaces too).

Try a command like : echo "cat lol.c | cat > lol.c"

Try anything except $.

If something crashes, select the "crash" flag.

If something doesn't work, select the "incomplete work" flag.

[**YES**](#)  |  [**NO**](#)


## **Return value of a process**

Execute a simple command with an absolute path like /bin/ls, or any other command with arguments but without any quotes and double quotes. Then execute echo $?

Check the printed value. You can do the same in bash in order to compare the results.

Repeat multiple times with different commands and arguments. Try some wrong commands like '/bin/ls filethatdoesntexist'

Try anything like expr $? + $?

If something crashes, select the "crash" flag.

If something doesn't work, select the "incomplete work" flag.

[**YES**](#)  |  [**NO**](#)


## **Relative Path**

Execute commands but this time use a relative path.

Repeat multiple times in different directories with a complex relative path (lots of ..).

[**YES**](#)  |  [**NO**](#)


## **unset**

Export environment variables, create new ones and replace old ones.

Use unset to remove some of them.

Check the result with env.

[**YES**](#)  |  [**NO**](#)


## **Environment variables**

Execute echo with some environment variables ($variable) as arguments.

Check that $ is interpreted as an environment variable.

Check that double quotes interpolate $.

Check that USER exists. Otherwise, set it.

echo "$USER" should print the value of the USER variable.

[**YES**](#)  |  [**NO**](#)


## **cd**

Use the command cd to move the working directory and check if you are in the right directory with /bin/ls

Repeat multiple times with working and not working cd

Also, try '.' and '..' as arguments.

[**YES**](#)  |  [**NO**](#)

# _Bonus Part_

## **Surprise! (or not...)**

Set the USER environment variable.

echo "'$USER'" should print the value of the USER variable.

echo '"$USER"' should print "$USER".

[**YES**](#)  |  [**NO**](#)


## **Wildcard**

Use wildcards in arguments in the current working directory.

[**YES**](#)  |  [**NO**](#)


## **And, Or**

Evaluate the bonus part if, and only if, the mandatory part has been entirely and perfectly done, and the error management handles unexpected or bad usage. In case all the mandatory points were not passed during the defense, bonus points must be totally ignored.

Use &&, || and parenthesis with commands and ensure minishell behaves the same way bash does.

[**YES**](#)  |  [**NO**](#)
