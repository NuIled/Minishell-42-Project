/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:49:26 by srachdi           #+#    #+#             */
/*   Updated: 2023/06/25 19:49:30 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void my_error(char *command,char * errmsg)//USE THIS
{
	ft_putstr_fd("minishell: ",STDERR_FILENO);
	ft_putstr_fd(command,STDERR_FILENO);
	ft_putstr_fd(" : ",STDERR_FILENO);
	ft_putstr_fd(errmsg,STDERR_FILENO);
	ft_putstr_fd("\n",STDERR_FILENO);
}

static void signal_handler(int signal)
{
	(void)signal;
	ft_putstr_fd("\nminishell> ",STDOUT_FILENO);
	rl_on_new_line();
	//rl_replace_line("",0); uncomment when readline added
	rl_redisplay();
	g_vars->status = 1;
}

void main_signal(void)//to be called in the main function
{
	if(signal(SIGINT,signal_handler) == SIG_ERR ||\
			signal(SIGQUIT,SIG_IGN) == SIG_ERR)
		my_error("signal:",strerror(errno));
	g_vars->status = 1;
}

void child_signal(void)//to be called after fork();
{
	if(signal(SIGINT,SIG_DFL) == SIG_ERR ||\
			signal(SIGQUIT,SIG_DFL) == SIG_ERR)
		my_error("signal:",strerror(errno));
	g_vars->status = 1;
}
