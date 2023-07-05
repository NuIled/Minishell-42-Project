/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:28:29 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/04 23:03:57 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exit_err(char *s, char *msg, int err_n)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (s)
		ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	g_vars->status = err_n;
}

static int	is_digit(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

void	ft_exit(t_cmd *cmd)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!cmd->argv[1])
	{
		g_vars->status = 0;
		exit(g_vars->status);
	}
	else if (cmd->argv[1] && !is_digit(cmd->argv[1]))
	{
		exit_err(cmd->argv[1], ": numeric argument required", 255);
		exit(g_vars->status);
	}
	else if (cmd->argv[2])
		exit_err(NULL, "too many arguments\n", 1);
	else
	{
		g_vars->status = ft_atoi(cmd->argv[1]);
		exit(g_vars->status);
	}
}
