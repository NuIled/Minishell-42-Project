/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:13:19 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/04 23:10:14 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	nflag(char *arg);
static void	echo_args(char **argv, int fd);

void	echo(t_cmd *cmd)
{
	int	nl;
	int	i;

	i = 1;
	nl = 1;
	if (!cmd->argv[i])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	while (cmd->argv[i] && nflag(cmd->argv[i]))
	{
		nl = 0;
		i++;
	}
	echo_args(&cmd->argv[i], STDOUT_FILENO);
	if (nl)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_vars->status = 0;
}

static int	nflag(char *arg)
{
	int	i;

	i = 1;
	if (!strcmp(arg, "-n"))
		return (1);
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	echo_args(char **argv, int fd)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], fd);
		if (argv[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
}
