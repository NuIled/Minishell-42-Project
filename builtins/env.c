/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:44:30 by srachdi           #+#    #+#             */
/*   Updated: 2023/06/25 19:45:42 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(void)
{
	t_env	*head;

	head = g_vars->env;
	update_last_cmd(get_path("env"));
	while (head)
	{
		printf ("%s=%s\n", head->var, head->value);
		head = head->next;
	}
	g_vars->status = 0;
}
