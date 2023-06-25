/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:41:17 by srachdi           #+#    #+#             */
/*   Updated: 2023/06/25 18:48:24 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	squotes(char *line, int i)
{
	int	flag;
	int	j;

	j = i;
	flag = 0;
	while (j >= 0)
	{
		if (line[j] == '\'' && flag == 0 && !dquotes(line, j))
			flag = 1;
		else if (line[j] == '\'' && flag == 1 && !dquotes(line, j))
			flag = 0;
		j--;
	}
	return (flag);
}

int	dquotes(char *line, int i)
{
	int	flag;
	int	j;

	flag = 0;
	j = i;
	while (j >= 0)
	{
		if (line[j] == '\"' && flag == 0 && !squotes(line, j))
			flag = 1;
		else if (line[j] == '\"' && flag == 1 && !squotes(line, j))
			flag = 0;
		j--;
	}
	return (flag);
}

int	var_quotes(char *s, int i, int d)
{
	if (squotes(s, i))
		return (1);
	else if (dquotes(s, i))
	{
		if (d && s[i] == '$')
			return (0);
		return (1);
	}
	return (0);
}
