/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:50:01 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/05 10:36:47 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	redir_out_error(char *path)
{
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": cannot access file or directory\n" \
		, STDERR_FILENO);
	return (-1);
}

int	redir_input(char *s, t_cmd *command, char *tmp, int mode)
{
	t_heredoc	*hd;
	int			err;

	hd = init_h();
	err = mode;
	while (s[++(hd->i)])
	{
		if (hd->is_open > 0)
			close(hd->is_open);
		if (s[hd->i] == '<' && !var_quotes(s, hd->i, 0))
		{
			if (is_heredoc(tmp, &hd->heredoc, &hd->i))
				err = set_stdin(hd->heredoc, command, hd->path, mode);
			else
			{
				hd->temp = word_after_redir(s, hd->i, 0);
				if (actual_file(&mode, &hd->path, \
						&hd->is_open, &hd->temp) == -1)
					return (-1);
				err = set_stdin(hd->heredoc, command, hd->path, mode);
			}
		}
	}
	free (hd);
	return (err);
}

int	redir_output(char *s, t_cmd *command, char *path, int n)
{
	int	i;
	int	o;

	i = 0;
	o = -1;
	while (s[i])
	{
		if (o > 0)
			close(o);
		if (s[i] == '>' && !var_quotes(s, i, 0))
		{
			cut_redirect(&n, &path, &i, s);
			o = ft_open(n, path);
			if (o < 0)
				return (redir_out_error(path));
		}
		i++;
	}
	command->append = n;
	command->out = path;
	return (n);
}
