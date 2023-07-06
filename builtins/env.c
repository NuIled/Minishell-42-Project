/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:44:30 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/06 03:53:41 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(void)
{
	t_env	*head;
	char	*en;

	en = "env";
	head = g_vars->env;
	ft_getcmd(&en, get_env_value("PATH"));
	update_last_cmd(en);
	while (head)
	{
		printf ("%s=%s\n", head->var, head->value);
		head = head->next;
	}
	g_vars->status = 0;
}
