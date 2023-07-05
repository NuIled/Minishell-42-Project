/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:05:35 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/04 22:59:19 by srachdi          ###   ########.fr       */
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
	g_vars->status = 1;
}

static char	*home(void)
{
	char	*home;

	home = get_env_value("HOME");
	if (!home)
	{
		my_error("cd", "Home not set");
		return (NULL);
	}
	chdir(home);
	return (ft_strdup(home));
}

static char	*oldpwd(void)
{
	char	*oldpwd;

	oldpwd = get_env_value("OLDPWD");
	if (!oldpwd)
	{
		my_error("cd", "OLDPWD not set");
		return (NULL);
	}
	chdir(oldpwd);
	return (ft_strdup(oldpwd));
}

static void	cd_update_env(char *var, char *value)
{
	if (get_env_value(var))
		update_env(var, value);
	else
	{
		add_to_env(var, value);
		free(value);
	}
}

void	cd(t_cmd *cmd)
{
	char	*path;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!cmd->argv[1] || !ft_strcmp(cmd->argv[1], "~") || \
		!ft_strcmp(cmd->argv[1], "--"))
		path = home();
	else if (!ft_strcmp(cmd->argv[1], "-"))
		path = oldpwd();
	else
	{
		if (chdir(cmd->argv[1]))
		{
			my_error("cd", "No such file or directory");
			return ;
		}
		path = ft_strdup(cmd->argv[1]);
	}
	if (!path)
		return ;
	g_vars->status = 0;
	cd_update_env("PWD", path);
	cd_update_env("OLDPWD", pwd);
}
