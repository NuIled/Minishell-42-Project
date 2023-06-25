/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:05:35 by srachdi           #+#    #+#             */
/*   Updated: 2023/06/25 19:12:08 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	my_error(char *command, char *errmsg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(" : ", STDERR_FILENO);
	ft_putstr_fd(errmsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	home(void)
{
	char	*home;

	home = get_env_value("HOME");
	if (!home)
	{
		my_error("cd", "Home not set");
		g_vars->status = 1;
		return ;
	}
	chdir(home);
}

void	cd(t_cmd *cmd)
{
	char	*path;
	char	pwd[4096 + 1];

	getcwd(pwd, 4096);
	if (!cmd->argv[1])
	{
		path = get_env_value("HOME");
		home();
	}
	else if (!ft_strcmp(cmd->argv[1], "~"))
	{
		path = get_env_value("HOME");
		home();
	}
	else if (!ft_strcmp(cmd->argv[1], "-"))
	{
		path = get_env_value("OLDPWD");
		chdir(path);
	}
	else
	{
		if (chdir(cmd->argv[1]) != 0)
		{
			my_error("cd", "No such file or directory");
			g_vars->status = 1;
			return ;
		}
		path = cmd->argv[1];
	}
	g_vars->status = 0;
	update_env("PWD", path);
	update_env("OLDPWD", pwd);
}
