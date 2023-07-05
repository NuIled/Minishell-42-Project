/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_it.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:46:23 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/04 23:12:53 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

char	*get_tkn(char *str, int *n)
{
	int	i;
	int	j;
	int	index;

	j = 0;
	i = *n;
	index = op_index(&str[i]);
	if (index < 0)
	{
		j = ft_strlen(&str[i]);
		*n += j;
		return (ft_substr(&str[i], 0, j));
	}
	if (!index)
	{
		while (str[i + j] && is_op(str[i + j]))
			j++;
		*n += j;
		return (ft_substr(&str[i], 0, j));
	}
	*n += index;
	return (ft_substr(&str[i], 0, index));
}

int	tkn_type(char *tkn)
{
	if (!ft_strcmp(tkn, "|"))
		return (PIPE);
	if (!ft_strcmp(tkn, "<<"))
		return (HD);
	if (!ft_strcmp(tkn, ">>"))
		return (RED);
	if (!ft_strcmp(tkn, "<") || !ft_strcmp(tkn, ">"))
		return (RED);
	if (is_op(tkn[0]))
		return (OP);
	else
		return (WRD);
}

t_tkn	*make_tkn(char *tkn)
{
	t_tkn	*node;

	node = ft_calloc(1, sizeof(t_tkn));
	node->token = tkn;
	node->type = tkn_type(tkn);
	node->next = NULL;
	return (node);
}

void	add_tkn(t_tkn **head, char *tkn)
{
	t_tkn	*tmp;
	t_tkn	*new;

	tmp = *head;
	new = make_tkn(tkn);
	if (!tmp)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_tkn	*tkn_it(char **arr)
{
	int		i;
	int		j;
	char	*tkn;
	t_tkn	*lst;

	i = 0;
	lst = NULL;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			tkn = get_tkn(arr[i], &j);
			add_tkn(&lst, tkn);
		}
		i++;
	}
	return (lst);
}
