/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:09:52 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/06 02:50:06 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d_arr(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free (arr);
	arr = NULL;
}

t_env	*create_node(char *var, char *value)
{
	t_env	*new_node;

	new_node = (t_env *) malloc (sizeof (t_env));
	if (!new_node)
	{
		printf ("Memory allocation failed.\n");
		return (NULL);
	}
	new_node->var = var;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	add_node(t_env **head, t_env *newNode)
{
	t_env	*temp;

	if (!*head)
		*head = newNode;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newNode;
	}
}

t_env	*get_env(char **env)
{
	int		i;
	t_env	*e;
	char	**arr;

	e = NULL;
	arr = NULL;
	i = -1;
	while (env[++i])
	{
		arr = ft_split(env[i], '=');
		if (!arr)
			return (NULL);
		if (arr[1])
			add_node(&e, create_node(ft_strdup(arr[0]), ft_strdup(arr[1])));
		else
			add_node(&e, create_node(ft_strdup(arr[0]), ft_strdup("")));
		free_2d_arr (arr);
	}
	return (e);
}

char	*get_env_value(char *var)
{
	t_env	*tmp;

	tmp = g_vars->env;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, var))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
