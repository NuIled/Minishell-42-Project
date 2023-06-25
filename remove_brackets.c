/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_brackets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:58:02 by srachdi           #+#    #+#             */
/*   Updated: 2023/06/25 19:04:39 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*increments i till after the word after angled brackets*/
void	i_after_w(char *buff, int *i)
{
	if (buff[*i + 1] && (buff[*i + 1] == '<' || buff[*i + 1] == '>'))
		(*i)++;
	while (buff[*i] \
			&& (buff[*i] == '<' || buff[*i] == '>' || ft_isspace(buff[*i])))
		(*i)++;
	while (buff[*i] && (!ft_isspace(buff[*i]) || var_quotes(buff, *i, 0)))
		(*i)++;
	while (buff[*i] && ft_isspace(buff[*i]))
		(*i)++;
}

/*removes angle brackedts and the word after them*/
char	*remove_brackets(char *s)
{
	int		i;
	char	*buff;
	char	*start;
	char	*end;

	i = 0;
	buff = ft_strdup(s);
	while (buff[i])
	{
		if ((buff[i] == '<' || buff[i] == '>') && !var_quotes(s, i, 0))
		{
			start = ft_substr(buff, 0, i);
			i_after_w(buff, &i);
			end = ft_substr(buff, i, ft_strlen(buff + i));
			free (buff);
			buff = ft_strjoin(start, end);
			free (start);
			free (end);
			i = -1;
		}
		i++;
	}
	free(s);
	return (buff);
}
