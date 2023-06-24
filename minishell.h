#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
#include <readline/readline.h>
 #include <readline/history.h>
# define READ_END 0
# define WRITE_END 1
#define MAX_PATH_LEN 4096
typedef struct s_heredoc
{
	int		i;
	int		is_open;
	char	**heredoc;
	char	*temp;
	char	*path;
}				t_heredoc;
typedef struct s_env
{		
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;
typedef struct s_shell {
	int				in;
	int				out;
	int				err;
	int				status;
	char			*entry;
	int				pid_count;
	int				*pids;
	t_env			*env;
}	t_shell;

/* We make t_shell global variable */

typedef struct s_cmd {
	char			*in;
	char			*out;
	int				heredoc;
	int				append;
	char			**argv;
	struct s_cmd	*next;
}	t_cmd;

t_shell	*g_vars;


//env.c
void free_2d_arr(char **arr);
t_env *createNode(char *var,char *val);
void addNode(t_env **head, t_env *node);
t_env *getEnv(char **env);
int ft_strcmp(char *s1,char *s2);
void update_env( char *var, char *val);
void checker(char *line);
int consecutive_char_count(char *s,char c);
void add_to_history(char *line);
void validate_redirection(char *line ,int *error);
void pipe_check(char *line,int i,int *error);
void check_pipe(char *line);
void parse(char *line);
void init_command(t_cmd *command);
void tokenize(char *line , t_cmd *command);
void execute(t_cmd *cmd);
int squotes(char *line ,int i);
int dquotes(char *line ,int i);
int var_quotes(char *s,int i, int d);
char *get_env_value(char *var);
char *expand(char *s);
void fill_command(char *s,t_cmd *command);
int redir_input(char *s,t_cmd *command , char *tmp,int n);
int redir_output(char *s,t_cmd *command,char *path,int n);
t_heredoc *init_h(void);
int is_heredoc(char *s,char ***hd,int *i,char **delimiter);
char *word_after_redir(char *s,int i,int rd );
char **get_delimiter(char *delimiter);
char *heredoc(char **del,t_cmd *cmd,char *s);
char *remove_quotes(char *s);
char * remove_brackets(char *s);
void free_array(char **array); 
char **sort_env(char **env);
void print_env(char **env);
char *get_var(char *s);
char *get_value(char *s, int i);
int valid_export(char *s);
char *str_char_str(char *path, char *cmd,char c);
int list_size(t_env *head);
void add_to_env(char *var ,char *value);
void append_to_env(char *var ,char *value);
/*exec utils*/
char *get_path(char *cmd);
int contain_char(char *s,char c);
/*signals*/
void child_signal(void);
void main_signal(void);
int is_builtin(char *cmd);
void exec_builtin(t_cmd *cmd);
/*builtins*/
void cd(t_cmd *cmd);
void echo(t_cmd *cmd);
void env(void);
void export(t_cmd *cmd);
void ft_exit(t_cmd *cmd);
void pwd(void);
void unset(t_cmd *cmd);
/**/
int ft_isspace(char c);
void print_sorted_env(void);
int count_args(char *line);
char **split_line_to_args(char *line);
void update_last_cmd(char *last_cmd);
void remove_env_node(char *var);
char **lst_to_arr_env(t_env *env);
#endif