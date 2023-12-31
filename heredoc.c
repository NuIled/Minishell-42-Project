/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:51:09 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/06 03:54:19 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*word_after_redir(char *s, int i, int rd)
{
	int	j;
	int	k;

	k = i + rd;
	if (!s[k])
		return (NULL);
	while (s[k] && ft_isspace(s[k]))
		k++;
	while (s[k] && (s[k] == '<' || s[k] == '>') && !var_quotes(s, k, 0))
		k++;
	while (s[k] && ft_isspace(s[k]))
		k++;
	j = k;
	while (s[j] && !ft_isspace(s[j]))
		j++;
	return (ft_substr(s, k, j - k));
}

char	**get_delimiter(char *delimiter)
{
	char	**arr;

	arr = malloc(sizeof(char *) * 2);
	if (!arr)
		return (NULL);
	arr[0] = delimiter;
	arr[1] = NULL;
	return (arr);
}

t_heredoc	*init_h(void)
{
	t_heredoc	*hd;

	hd = malloc(sizeof(t_heredoc));
	if (!hd)
		return (perror("malloc error\n"), NULL);
	hd->path = NULL;
	hd->i = -1;
	hd->heredoc = NULL;
	hd->temp = NULL;
	hd->is_open = -1;
	return (hd);
}

int	is_heredoc(char *s, char ***hd, int *i)
{
	if (s[*i + 1] && s[*i + 1] == '<')
	{
		*hd = get_delimiter(word_after_redir(s, *i + 1, 1));
		*i += 2;
		return (1);
	}
	return (0);
}

char	*heredoc(char **del, t_cmd *cmd)
{
	int		i;
	int		exp;
	char	*line;
	char	*line_nl;
	char	*joined;

	line = NULL;
	line_nl = NULL;
	joined = NULL;
	i = 0;
	exp = xpnd(del);
	while (del[i])
	{
		line = readline("\033[1;35m>\033[0m ");
		if (!line)
			break ;
		if (exp && *line)
			line = expand(line);
		line_nl = ft_strjoin(line, "\n");
		if (!ft_strcmp(line, del[i]))
			i++;
		if (del[i])
			joined = store_line(joined, line_nl);
		free(line);
		free(line_nl);
	}
	free_array(del);
	cmd->heredoc = 1;
	return (joined);
}
