/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:55:26 by aoutifra          #+#    #+#             */
/*   Updated: 2023/07/05 19:32:24 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_getcmd(char **cmd, char *path)
{
	char	*command;
	char	**pathsplited;

	command = *cmd;
	pathsplited = ft_split(path, ':');
	if (strrchr(*cmd, '/'))
		return ;
	while (*pathsplited)
	{
		path = ft_strjoin(*pathsplited, "/");
		*cmd = ft_strjoin(path, command);
		if (!access(*cmd, X_OK))
		{	
			free(path);
			free(command);
			free(pathsplited);
			return ;
		}
		pathsplited++;
		free(*pathsplited);
	}
			free(path);
			free(command);
	//free_2d_arr(pathsplited);
}

void	close_fd(int fd[2])
{
	close(fd[1]);
	close(fd[0]);
}

void	check_fd(t_cmd *cmd, int fd[2])
{
	int	in;
	int	out;

	if (cmd->heredoc)
	{
		write(fd[1], cmd->in, ft_strlen(cmd->in));
		dup2(fd[0], 0);
		return ;
	}
	if (cmd->in)
	{
		in = open(cmd->in, O_RDONLY, 0664);
		dup2(in, STDIN_FILENO);
	}
	if (cmd->out)
	{
		if (cmd->append)
			out = open(cmd->out, O_CREAT | O_RDWR | O_APPEND, 0664);
		else
			out = open(cmd->out, O_CREAT | O_TRUNC, 0664);
		dup2(out, STDOUT_FILENO);
	}
	return ;
}

void	ft_error(char *cmd, char *err)
{
	if (cmd && errno != 13)
	{
		printf("minishell %s: command not found\n", err);
		g_vars->status = 127;
		return ;
	}
	else if (errno == 13)
	{
		printf("minishell %s: Permission denied \n", err);
		g_vars->status = 126;
		return ;
	}
	else
		printf("minishell %s: %s \n", err, (char *)(strerror(errno)));
	g_vars->status = errno;
}

void	execute(t_cmd *cmd)
{
	int		pipefd[2];
	int		pid;
	char	*err = 0;

	while (cmd)
	{
		if (cmd->argv[0] && !ft_strncmp(cmd->argv[0], "exit", 4))
			ft_exit(cmd);
		pipe(pipefd);
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		if (pid == 0)
			execute_chiled(pipefd, cmd, err);
		dup2(pipefd[0], 0);
		close_fd(pipefd);
		wait(&g_vars->status);
		if (g_vars->status == 2)
			g_vars->status += 128;
		if (g_vars->status == 0)
			{
				ft_getcmd(cmd->argv, get_env_value("PATH"));
				update_last_cmd(ft_strdup(cmd->argv[0]));
			}
		cmd = cmd->next;
	}
	dup2(g_vars->out, STDOUT_FILENO);
	dup2(g_vars->in, STDIN_FILENO);
}
