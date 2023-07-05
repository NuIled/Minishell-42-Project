/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tkns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:46:58 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/04 23:17:13 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

/*1 is bad ,0 is good*/
int	invalid_op(t_tkn *head)
{
	while (head)
	{
		if (head->type == OP)
			return (1);
		head = head->next;
	}
	return (0);
}
/*1 is bad ,0 is good*/

int	invalid_red(t_tkn *head)
{
	while (head)
	{
		if (head->type == RED || head->type == HD)
		{
			if (head->next)
			{
				if (head->next->type != WRD)
					return (1);
			}
			else
				return (1);
		}
		head = head->next;
	}
	return (0);
}
/*checks if there is a string  after pipe*/

int	wrd_after_pipe(t_tkn *head)
{
	head = head->next;
	while (head && head->type != PIPE)
	{
		if (head->type == WRD)
			return (1);
		head = head->next;
	}
	return (0);
}

/*1 is bad ,0 is good*/
/*checks if there is a word after and before pipe */
int	invalid_pipe(t_tkn *head)
{
	int	flag;

	flag = 0;
	while (head)
	{
		if (head->type == WRD)
			flag = 1;
		if (head->type == PIPE)
		{
			if (!flag || !wrd_after_pipe(head))
				return (1);
			flag = 0;
		}
		head = head->next;
	}
	return (0);
}

int	check_tkns(t_tkn *lst)
{
	if (invalid_op(lst))
		return (0);
	if (invalid_red(lst))
		return (0);
	if (invalid_pipe(lst))
		return (0);
	return (1);
}
