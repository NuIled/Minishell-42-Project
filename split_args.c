/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:49:05 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/05 10:33:29 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		if (line[i] && !var_quotes(line, i, 0) && !ft_isspace(line[i]))
		{
			count++;
			while (line[i] && !ft_isspace(line[i]))
				i++;
			continue ;
		}
		i++;
	}
	return (count);
}

int	arg_len(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		if (!var_quotes(line, i, 0) && ft_isspace(line[i]))
			return (i);
		i++;
	}
	return (i);
}

char	*get_arg(char *line, int *i)
{
	char	*arg;
	int		j;
	int		k;

	arg = malloc(sizeof(char) * (arg_len(line) + 1));
	if (!arg)
		return (NULL);
	j = 0;
	k = 0;
	while (line[j] && ft_isspace(line[j]))
		j++;
	while (line[j])
	{
		if (!var_quotes(line, j, 0) && ft_isspace(line[j]))
			break ;
		arg[k] = line[j];
		k++;
		j++;
	}
	arg[k] = '\0';
	while (line[j] && ft_isspace(line[j]))
		j++;
	*i += j;
	return (arg);
}

char	**split_line_to_args(char *line)
{
	int		count;
	int		i;
	int		j;
	char	**args;

	i = 0;
	j = 0;
	count = 0;
	count = count_args(line);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	while (line[i])
	{
		args[j] = get_arg(line + i, &i);
		if (!args[j])
			return (free_2d_arr(args), NULL);
		j++;
	}
	args[j] = NULL;
	free(line);
	return (args);
}
