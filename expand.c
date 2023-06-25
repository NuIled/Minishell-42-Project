/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:18:28 by srachdi           #+#    #+#             */
/*   Updated: 2023/06/25 18:24:52 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*ft_cpy_new_line(char *cmd, char *var_env, char *new, int i)
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
	free (cmd);
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
		return (NULL);
	j = 0;
	while (j < i && cmd)
	{
		new[j] = cmd[j];
		j++;
	}
	new[j] = '\0';
	new = ft_cpy_new_line(cmd, var_env, new, i);
	return (new);
}

char	*extract_var(char *s, int index)
{
	int		i;
	int		j;
	char	*var;

	i = index + 1;
	i = var_len (s, i);
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (NULL);
	i = index + 1;
	j = 0;
	while (s[i] && (valid_env_var(s[i]) || s[i] == '?'))
	{
		var[j] = s[i];
		j++;
		if (s[j] == '?')
			break ;
		i++;
	}
	var[j] = '\0';
	return (var);
}

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
		if (line[i] == '\'' && !(dq % 2))
			sq++;
		if (line[i] == '\"' && !(sq % 2))
			dq++;
		i++;
	}
	if (sq % 2)
		return (0);
	return (1);
}

char	*expand(char *s)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && closed_sq(s, i) \
				&& (valid_env_var(s[i + 1]) || s[i + 1] == '?'))
		{
			var = extract_var(s, i);
			if (!ft_strcmp(var, "?"))
				value = ft_itoa(g_vars->status);
			else
				value = get_env_value(var);
			free(var);
			var = copy_value(s, value, i);
			if (more_vars(var))
				var = expand(var);
			return (var);
		}
		i++;
	}
	return (s);
}
