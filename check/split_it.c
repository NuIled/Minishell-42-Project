/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_it.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:46:43 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/04 23:15:55 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

/*count the number of words ,if the string is inisde quotes it counts as 1 */
int	wc(char *line)
{
	int	i;
	int	n;
	int	j;

	i = 0;
	n = 0;
	j = 1;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
		{
			if (line[i] == '\'' || line[i] == '\"')
				i = in_q(line, line[i], i + 1);
			if (i < 0)
				return (-1);
			if (j)
				n++;
			j = 0;
		}
		else
			j = 1;
		i++;
	}
	return (n);
}

char	*word(char *line, int *n)
{
	int		i;
	int		j;
	int		k;
	char	*s;

	i = *n;
	k = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	j = i;
	while (line[i] && !ft_isspace(line[i]))
	{
		if (is_q(line[i]))
			i = in_q(line, line[i], i + 1);
		i++;
	}
	s = ft_calloc(i - j + 1, sizeof(char));
	while (j < i)
	{
		s[k] = line[j];
		k++;
		j++;
	}
	*n = i;
	return (s);
}

char	**split_it(char *line)
{
	int		i;
	int		j;
	int		count;
	char	**arr;

	i = 0;
	j = 0;
	count = wc(line);
	if (count < 0)
		return (NULL);
	arr = ft_calloc((count + 1), sizeof(char *));
	while (i < count)
	{
		arr[i] = word(line, &j);
		i++;
	}
	return (arr);
}

int	op_index(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_q(str[i]))
			i = in_q(str, str[i], i + 1);
		if (is_op(str[i]))
			return (i);
		i++;
	}
	return (-1);
}

void	freedom(char *s, char **arr, t_tkn *lst)
{
	free (s);
	free_array (arr);
	free_tkn_list (lst);
}
