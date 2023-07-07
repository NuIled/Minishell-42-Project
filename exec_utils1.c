/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 03:50:26 by aoutifra          #+#    #+#             */
/*   Updated: 2023/07/06 20:20:46 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_last_cmd(char *last_cmd)
{
	if (last_cmd && *last_cmd
		&& (!access(last_cmd, X_OK) || is_builtin(last_cmd)))
	{
		remove_env_node("_");
		add_to_env("_", last_cmd);
		free(last_cmd);
		return ;
	}
	free(last_cmd);
}

void	check_exit_status(int *status, t_cmd *cmd)
{
	if (WIFEXITED(*status) && WEXITSTATUS(*status) != 2)
		g_vars->status = WEXITSTATUS(*status);
	else
		g_vars->status = 130;
	if (g_vars->status == 0)
	{
		if (!is_builtin(cmd->argv[0]))
			ft_getcmd(cmd->argv, get_env_value("PATH"));
		update_last_cmd(ft_strdup(cmd->argv[0]));
	}
}

int	xpnd(char **del)
{
	if (contain_char(*del, '\'') || contain_char(*del, '\"'))
	{
		*del = remove_quotes(*del);
		return (0);
	}
	return (1);
}
