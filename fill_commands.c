#include "./minishell.h"
int count_until_specials(char *s, int i)
{
	while (s[i] && s[i] != ' ' && s[i] != '?' &&
		   s[i] != '?' && s[i] != '$' && s[i] != '\"' && s[i] != '\'')
		i++;
	return i;
}
// int ft_isspace(char c)//IN LIBFT NOW
// {
//     if( c == ' ' || c == '\t' || c == '\n' || c == '\v'\
// 		|| c == '\f' || c == '\r')
//         return 1;
//     else
//         return 0;
// }
int letter_count(char *s)
{
	int len = 0;
	len = ft_strlen(s);
	if (!len)
		return 1;
	while (*s && ft_isspace(*s))
		s++, len--;
	return len;
}

char *skip_space(char *s)
{
	int i = 0;
	char *str;

	if (letter_count(s) == 0)
		return s;
	while (s[i] && ft_isspace(s[i]))
		i++;
	str = ft_substr(s, i, ft_strlen(s) - i);
	if (!str)
		return NULL;
	free(s);
	return str;
}
void fill_err(t_cmd *cmd)
{
	cmd->argv = malloc(2 * sizeof(char *));
	cmd->argv[0] = malloc(2);
	cmd->argv[1] = NULL;
	cmd->argv[0][0] = 1;
	cmd->argv[0][1] = 0;
	cmd->heredoc = 0;
	if (cmd->in)
		free(cmd->in);
	cmd->in = NULL;
	if (cmd->out)
		free(cmd->out);
	cmd->out = NULL;
	cmd->next = NULL;
}

void free_stuff(char *a, char *b, char *c, char *d)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
	if (d)
		free(d);
}
void without_quotes_args(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->argv[i])
	{
		cmd->argv[i] = remove_quotes(cmd->argv[i]);
		i++;
	}
	if (cmd->out)
		cmd->out = remove_quotes(cmd->out);
	if (cmd->in)
		cmd->in = remove_quotes(cmd->in);
}

void fill_command(char *s, t_cmd *command)
{
	char *expanded;
	char *args;
	char *tmp;
	int err1;
	int err2;
	args = NULL;
	tmp = skip_space(ft_strdup(s));
	free(s);
	err1 = redir_input(tmp, command, tmp, 0);	 // THIS WORKS
	err2 = redir_output(tmp, command, NULL, 0); // THIS WORKS
	tmp = remove_brackets(tmp);
	expanded = expand(tmp);
	if ((err1 == -1 && err2 == -1) || err1 == -2)
	{
		fill_err(command);
	
	}
	command->argv = split_line_to_args(expanded);
	without_quotes_args(command);
	command->next = NULL;
}