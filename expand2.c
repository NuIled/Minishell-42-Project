#include "./minishell.h"

/*if char is a number or a letter ot '_' return 1, else return 0*/
int valid_env_var(char c)
{
    if(ft_isalnum(c) || c == '_')
        return (1);
    return (0);
}

/*counts the lenght of the word after '$' */
int	var_len(char *s, int i)
{
	while (s[i] && (valid_env_var(s[i]) || s[i] == '?'))
	{
		if (s[i] == '?')
			break ;
		i++;
	}

	return (i);
}

int	ft_strlen_var(char *str, int j)
{
	int	i;

	i = 1;
	j++;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_' || str[j] == '?'))
	{
		i++;
		if (str[j] == '?')
			break ;
		j++;
	}
	return (i);
}
char	*ft_cpy_new_line_bis(char *cmd, char *var_env, char *new, int i)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	while (new[j])
		j++;
	while (var_env && var_env[k])
	{
		new[j] = var_env[k];
		j++;
		k++;
	}
	k = i + ft_strlen_var(cmd, i);
	while (cmd[k] && cmd)
	{
		new[j] = cmd[k];
		j++;
		k++;
	}
	new[j] = '\0';
	free(cmd);
	return (new);
}

char	*copy_value(char *cmd, char *var_env, int i)
{
	int		j;
	char	*new;

	j = ft_strlen(cmd) - ft_strlen_var(cmd, i);
	if (var_env)
		j += ft_strlen(var_env);
	new = malloc(sizeof(char) * (j + 1));
	if (!new)
		return NULL;
	j = 0;
	while (j < i && cmd)
	{
		new[j] = cmd[j];
		j++;
	}
	new[j] = '\0';
	new = ft_cpy_new_line_bis(cmd, var_env, new, i);
	return (new);
}

char *extract_var(char *s,int index)
{
    int i;
    int j;
    char *var;

    i = index + 1;
    i =  var_len(s,i);
    var = malloc(sizeof(char) * (i + 1));
    if(!var)
        return NULL;//malloc error
    i = index + 1;
    j = 0;
    while (s[i] && (valid_env_var(s[i]) || s[i] == '?'))
    {
       var[j] = s[i];
       j++;
       if(s[j] == '?')
            break;
        i++;
    }
    var[j] = '\0';
    return (var);
}
/*checks if the single quotes before index are closed , closed : 1 , open : 0 */
int	closed_sq(char *line, int index)
{
	int	sq;
	int	dq;
	int	i;

	i = 0;
	sq = 0;
	dq = 0;
	while (i < index)
	{
		if (line[i] =='\'' && !(dq % 2) )
			sq++;
		if (line[i] == '\"' && !(sq % 2))
			dq++;
		i++;
	}
	if (sq % 2)
		return (0);
	return (1);
}

int	non_space_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			count++;
		i++;
	}
	return (count);
}
/*checks if there is '$' in s ,so we run expand() again*/
int	more_vars(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	if ((size_t)i != ft_strlen(s))
		return (1);
	return (0);
}
/*expand function : expands the word after $ if no inside single quotes*/
char *expand(char *s)
{
    int i;
    char *var;
    char *value;

    i = 0;
    while(s[i])
    {
        if(s[i] == '$'  && s[i + 1] && closed_sq(s, i) \
		&& (valid_env_var(s[i + 1]) || s[i + 1] == '?'))
        {
            var = extract_var(s,i);
			if(!ft_strcmp(var,"?"))
				value = ft_itoa(g_vars->status);
            else 
				value = get_env_value(var);
            free(var);
            var = copy_value(s,value,i);
            if(more_vars(var))
                var = expand(var);
            return (var);
        }
        i++;
    }
    return (s);
}