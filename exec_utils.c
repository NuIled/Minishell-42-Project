/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 03:47:32 by aoutifra          #+#    #+#             */
/*   Updated: 2023/07/06 05:01:09 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contain_char(char *s, char c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

void	execute_chiled(int pipefd[2], t_cmd *cmd, char *err)
{
	if (!cmd->argv[0])
		exit(0);
	err = cmd->argv[0];
	check_fd(cmd, pipefd);
	dup2(pipefd[1], STDOUT_FILENO);
	close_fd(pipefd);
	if (!cmd->next && !cmd->out)
		dup2(g_vars->out, STDOUT_FILENO);
	if (is_builtin(cmd->argv[0]))
		exec_builtin(cmd);
	ft_getcmd(cmd->argv, get_env_value("PATH"));
	execve(cmd->argv[0], cmd->argv, lst_to_arr_env(g_vars->env));
	ft_error(cmd->argv[0], err);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		free_2d_arr(tmp->argv);
		if (tmp->in)
			free(tmp->in);
		if (tmp->out)
			free(tmp->out);
		cmd = cmd->next;
		free(tmp);
	}
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	exec_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		cd(cmd);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		pwd();
	else if (!ft_strcmp(cmd->argv[0], "export"))
		export(cmd);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		unset(cmd);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		env();
	exit(g_vars->status);
}
