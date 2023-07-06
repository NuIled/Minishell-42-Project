/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:00:08 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/06 01:28:20 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_history(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (*line && i < (int)ft_strlen(line))
	{
		add_history(line);
		if (check_line(line))
			parse (line);
		else
			free (line);
	}
	else
		free (line);
}

void	init_g_var(char **env)
{
	g_vars = malloc (sizeof (t_shell));
	g_vars->in = dup (STDIN_FILENO);
	g_vars->out = dup (STDOUT_FILENO);
	g_vars->err = dup (STDERR_FILENO);
	g_vars->env = get_env (env);
	g_vars->status = 0;
	shlvl ();
	main_signal ();
}

void	minishell(void)
{
	int		i;
	char	*line;

	i = 0;
	while (1)
	{
		line = readline ("\033[1m\033[36mminishell$ \033[0m");
		if (!line)
			end_it ();
		add_to_history (line);
	}
}

int	main(int ac, char **av, char **env)
{
	(void) av;
	if (ac == 1)
	{
		init_g_var (env);
		minishell ();
	}
	else
	{
		printf ("Try : ./minishell\n");
		return (1);
	}
}
