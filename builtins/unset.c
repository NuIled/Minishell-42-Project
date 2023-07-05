/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:24:39 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/05 10:54:05 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_env_node(char *var)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = g_vars->env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, var))
		{
			if (prev)
				prev->next = tmp->next;
			else
				g_vars->env = tmp->next;
			free(tmp->var);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

static int	is_valid(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (0);
	i++;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	unset(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->argv[i])
	{
		g_vars->status = 0;
		return ;
	}
	while (cmd->argv[i])
	{
		if (!is_valid(cmd->argv[i]))
		{
			ft_putstr_fd("minishell: unset ", STDERR_FILENO);
			ft_putstr_fd(cmd->argv[i], STDERR_FILENO);
			ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
			g_vars->status = 1;
			i++;
			continue ;
		}
		remove_env_node(cmd->argv[i]);
		i++;
	}
}

void	free_array(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}
