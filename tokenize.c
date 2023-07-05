/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:48:46 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/04 23:31:37 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_words(char *line, char c);
char	*make_word(char *line, char c);
char	**split_tokens(char *line, char c);
void	tokenize(char *line, t_cmd *command);

int	count_words(char *line, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] == c)
			i++;
		if (((line[i] != c && ((!var_quotes(line, i, 0) && (line[i] != '\"' \
				&& line[i] != '\'')) || (var_quotes(line, i, 0) \
				&& (line[i] == '\'' || line[i] == '\"'))))) && line[i])
			count++;
		while ((line[i] != c || var_quotes(line, i, 0)) && line[i])
			i++;
	}
	return (count);
}

char	*make_word(char *line, char c)
{
	int		i;
	char	*s;

	i = 0;
	while (line[i] && (line[i] != c || var_quotes(line, i, 0)))
		i++;
	s = ft_calloc(i + 1, sizeof(char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, line, i + 1);
	return (s);
}

char	**split_tokens(char *line, char c)
{
	int		i;
	int		count;
	char	**arr;

	i = -1;
	if (!line)
		return (NULL);
	count = count_words(line, c);
	arr = ft_calloc(count + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	while (++i < count)
	{
		while (*line == c && !var_quotes(line, 0, 0))
			line++;
		arr[i] = make_word(line, c);
		if (!arr[i])
			return (free_2d_arr(arr), NULL);
		line += ft_strlen(arr[i]);
	}
	arr[i] = NULL;
	return (arr);
}

void	tokenize(char *line, t_cmd *command)
{
	int		i;
	char	**arr;

	i = 0;
	arr = split_tokens(line, '|');
	free(line);
	if (!arr)
		cmd_error (command);
	while (arr[i])
	{
		fill_command(arr[i], command);
		if (arr[i + 1])
		{
			command->next = malloc(sizeof(t_cmd));
			if (!command->next)
				return ;
			init_command(command->next);
		}
		command = command->next;
		i++;
	}
	free(arr);
}
