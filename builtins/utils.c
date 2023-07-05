/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:18:27 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/04 23:01:26 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(char *var, char *new_value)
{
	t_env	*head;

	head = g_vars->env;
	if (!head || !var || !new_value)
		return ;
	while (head)
	{
		if (!ft_strcmp(var, head->var))
		{
			free(head->value);
			head->value = ft_strdup(new_value);
			free(new_value);
		}
		head = head->next;
	}
}

void	add_to_env(char *var, char *value)
{
	if (!g_vars->env || !var || !value)
		return ;
	add_node(&g_vars->env, create_node(ft_strdup(var), ft_strdup(value)));
}

void	append_to_env(char *var, char *value)
{
	char	*new_value;
	t_env	*head;

	head = g_vars->env;
	if (!head || !var || !value)
		return ;
	while (head)
	{
		if (!ft_strcmp(var, head->var))
		{
			new_value = ft_strjoin(head->value, value);
			free(head->value);
			head->value = new_value;
		}
		head = head->next;
	}
}

int	list_size(t_env *head)
{
	int		count;
	t_env	*ptr;

	if (!head)
		return (0);
	ptr = head;
	count = 0;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

char	*str_char_str(char *path, char *cmd, char c)
{
	char	*s;
	int		len;
	int		i;
	int		j;

	i = -1;
	if (!path || !cmd)
		return (NULL);
	len = strlen(path) + strlen(cmd) + 2;
	s = (char *)malloc(sizeof(char) * len);
	if (!s)
		return (perror("malloc failed\n"), NULL);
	while (path[++i])
		s[i] = path[i];
	s[i] = c;
	j = i + 1;
	i = -1;
	while (cmd[++i])
		s[j++] = cmd[i];
	s[j] = '\0';
	return (s);
}
