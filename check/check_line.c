/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:20:28 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/04 23:21:02 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

void	free_tkn_list(t_tkn *head)
{
	t_tkn	*tmp;

	while (head)
	{
		tmp = head;
		free(head->token);
		head = head->next;
		free(tmp);
	}
}

/*check if there is a matching qoute*/
int	in_q(char *line, char q, int i)
{
	while (line[i])
	{
		if (line[i] == q)
			return (i);
		i++;
	}
	return (-1);
}

int	is_op(char c)
{
	if (c == '&' || c == ';' || c == '(')
		return (1);
	if (c == ')' || c == '>' || c == '<')
		return (1);
	if (c == '|')
		return (1);
	return (0);
}

int	is_q(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	check_line(char *line)
{
	char	**arr;
	t_tkn	*lst;
	char	*s;

	lst = NULL;
	s = ft_strdup(line);
	arr = split_it(s);
	if (!arr)
	{
		g_vars->status = SYNTAX_ERR;
		ft_putstr_fd("minishell : syntax error\n", STDERR_FILENO);
		freedom(s, arr, lst);
		return (0);
	}
	lst = tkn_it(arr);
	if (!check_tkns(lst))
	{
		g_vars->status = SYNTAX_ERR;
		freedom(s, arr, lst);
		ft_putstr_fd("minishell : syntax error\n", STDERR_FILENO);
		return (0);
	}
	freedom(s, arr, lst);
	return (1);
}
