/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:44:30 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/05 19:00:13 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(void)
{
	t_env	*head;

	head = g_vars->env;
	char *en = "env";
	ft_getcmd(&en, get_env_value("PATH"));
	update_last_cmd(en);
	while (head)
	{
		printf ("%s=%s\n", head->var, head->value);
		head = head->next;
	}
	g_vars->status = 0;
}
