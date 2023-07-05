/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:49:15 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/05 10:41:17 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	without_quotes_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		cmd->argv[i] = remove_quotes(cmd->argv[i]);
		i++;
	}
	if (cmd->out)
		cmd->out = remove_quotes(cmd->out);
	if (cmd->in)
		cmd->in = remove_quotes(cmd->in);
}

void	fill_command(char *s, t_cmd *command)
{
	char	*expanded;
	char	*tmp;
	int		err1;
	int		err2;

	tmp = skip_space(ft_strdup(s));
	free (s);
	err1 = redir_input(tmp, command, tmp, 0);
	err2 = redir_output(tmp, command, NULL, 0);
	tmp = remove_brackets(tmp);
	expanded = expand(tmp);
	if ((err1 == -1 && err2 == -1) || err1 == -2)
	{
		fill_err(command);
	}
	command->argv = split_line_to_args(expanded);
	without_quotes_args (command);
	command->next = NULL;
}
