/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:26:27 by srachdi           #+#    #+#             */
/*   Updated: 2023/06/25 18:36:57 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
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
# include <readline/readline.h>
# include <readline/history.h>
# include "check/check.h"

# define READ_END 0
# define WRITE_END 1
# define MAX_PATH_LEN 4096

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
	int				pid_count;
	int				*pids;
	t_env			*env;
}	t_shell;

/* global struct */
typedef struct s_cmd {
	char			*in;
	char			*out;
	int				heredoc;
	int				append;
	char			**argv;
	struct s_cmd	*next;
}	t_cmd;

t_shell	*g_vars;

/*check*/
int			check_line(char *line);
/*builtins*/
void		cd(t_cmd *cmd);
void		echo(t_cmd *cmd);
void		env(void);
void		export(t_cmd *cmd);
void		ft_exit(t_cmd *cmd);
void		pwd(void);
void		unset(t_cmd *cmd);
char		*str_char_str(char *path, char *cmd, char c);
int			list_size(t_env *head);
void		append_to_env(char *var, char *value);
void		add_to_env(char *var, char *value);
void		update_env(char *var, char *new_value);
void		free_array(char **array);
char		**sort_env(char **env);
void		print_env(char **env);
int			valid_export(char *s);
char		*get_var(char *s);
char		*get_value(char *s, int i);
/**/
void		print_sorted_env(void);
int			count_args(char *line);
char		**split_line_to_args(char *line);
void		update_last_cmd(char *last_cmd);
void		remove_env_node(char *var);
char		**lst_to_arr_env(t_env *env);
/*utils.c*/
void		shlvl(void);
void		end_it(void);
char		*remove_quotes(char *str);
int			ft_strcmp(char *s1, char *s2);
int			consecutive_char_count(char *s, char c);
/*tokenize.c*/
int			count_words(char *line, char c);
char		*make_word(char *line, char c);
char		**split_tokens(char *line, char c);
void		tokenize(char *line, t_cmd *command);
/*utils_2.c*/
void		ignore_signals(void);
void		free_env_list(t_env *env);
/*env.c*/
void		free_2d_arr(char **arr);
t_env		*create_node(char *var, char *val);
void		add_node(t_env **head, t_env *node);
t_env		*get_env(char **env);
char		*get_env_value(char *var);
int			list_size(t_env *head);
void		free_2d_arr(char **arr);
/*execute*/
int			cmd_list_size(t_cmd *head);
void		dupping(void);
void		free_cmd_list(t_cmd *head);
void		exc_dup(t_cmd *cmd);
void		exc_err(char *s, char *msg);
void		x_cmd(t_cmd *cmd);
pid_t		exc_one(t_cmd *command, int i);
pid_t		exc_one(t_cmd *command, int i);
pid_t		exc_heredoc(t_cmd *cmd);
pid_t		exc_pipe(t_cmd *cmd);
int			exc(t_cmd *cmd, int i);
void		exc_wait(t_cmd *cmd, int n);
void		execute(t_cmd *cmd);
/*exec_utils.c*/
int			contain_char(char *s, char c);
char		*get_path(char *cmd);
char		*get_path2(char *cmd);
void		free_cmd(t_cmd *cmd);
int			is_builtin(char *cmd);
void		exec_builtin(t_cmd *cmd);
void		update_last_cmd(char *last_cmd);
/*expand.c && expand_utils.c*/
int			valid_env_var(char c);
int			var_len(char *s, int i);
int			ft_strlen_var(char *str, int j);
char		*ft_cpy_new_line(char *cmd, char *var_env, char *new, int i);
char		*copy_value(char *cmd, char *var_env, int i);
char		*extract_var(char *s, int index);
int			closed_sq(char *line, int index);
int			non_space_count(char *str);
int			more_vars(char *s);
char		*expand(char *s);
/*fill_command.c and fill_command_utils.c*/
int			count_until_specials(char *s, int i);
int			letter_count(char *s);
char		*skip_space(char *s);
void		fill_err(t_cmd *cmd);
void		free_stuff(char *a, char *b, char *c, char *d);
void		without_quotes_args(t_cmd *cmd);
void		fill_command(char *s, t_cmd *command);
/*heredoc.c*/
char		*word_after_redir(char *s, int i, int rd );
char		**get_delimiter(char *delimiter);
t_heredoc	*init_h(void);
int			is_heredoc(char *s, char ***hd, int *i, char **delimiter);
char		*heredoc(char **del, t_cmd *cmd, char *s);
/*parse_utils.c*/
int			squotes(char *line, int i);
int			dquotes(char *line, int i);
int			var_quotes(char *s, int i, int d);
/*parse.c*/
void		init_command(t_cmd *command);
t_cmd		*line_to_cmd(char *line);
void		parse(char *line);
/*redirect_input.c*/
char		*store_line(char *s, char *line);
int			actual_file(int *n, char **path, int *o, char **tmp);
int			set_stdin(char **dlmtr, t_cmd *cmd, char *path, int n);
/*redirect_output*/
int			ft_open(int mode, char *filename);
void		cut_redirect(int *n, char **path, int *i, char *s);
/*redirection*/
int			redir_input(char *s, t_cmd *command, char *tmp, int mode);
int			redir_output(char *s, t_cmd *command, char *path, int n);
/*remove_brackets*/
void		i_after_w(char *buff, int *i);
char		*remove_brackets(char *s);
/*signals*/
void		main_signal(void);
void		child_signal(void);
/*split_args.c*/
int			count_args(char *line);
int			arg_len(char *line);
char		*get_arg(char *line, int *i);
char		**split_line_to_args(char *line);
#endif
