/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:49:47 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/05 10:43:32 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*store_line(char *s, char *line)
{
	char	*joined;

	if (s)
		joined = ft_strjoin(s, line);
	else
		joined = ft_strdup(line);
	free (s);
	return (joined);
}

int	set_stdin(char **dlmtr, t_cmd *cmd, char *path, int n)
{
	char	*tmp;

	if (dlmtr && !path)
	{
		tmp = heredoc(dlmtr, cmd);
		if (!tmp)
			return (-2);
		cmd->in = tmp;
	}
	else
	{
		cmd->in = path;
		cmd->append = n;
		cmd->heredoc = 0;
	}
	return (n);
}

int	actual_file(int *n, char **path, int *o, char **tmp)
{
	*n = 1;
	*path = remove_quotes(*tmp);
	*o = open(*path, O_RDONLY);
	if (*o < 0)
	{
		ft_putstr_fd(*path, STDERR_FILENO);
		ft_putstr_fd(" : cannot access file or directory\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}
