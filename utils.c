/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:48:17 by srachdi           #+#    #+#             */
/*   Updated: 2023/06/25 19:48:21 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int consecutive_char_count(char *s,char c)
{

	int count = 0;
	if(!s || !c)
		return 0;
	while(*s && *s == c)
	{
		count++;
		s++;
	}
	return count;
}

int ft_strcmp(char *s1,char *s2)
{
	while(*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}


char *remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if ((str[i] == '\'' && !dquotes(str, i))
				|| (str[i] == '\"' && !squotes(str, i)))
		{
			i++;
			continue ;
		}
		result[j] = str[i];
		i++;
		j++;
	}
	result[j] = '\0';
	free(str);
	return (result);
}

void end_it(void)
{
	free_env_list(g_vars->env);
	free(g_vars);
	ft_putstr_fd("exit\n",STDOUT_FILENO);
	exit(0);
}

void shlvl(void)
{
	char *lvl;

	lvl = get_env_value("SHLVL");
	if(lvl) 
		update_env("SHLVL",ft_itoa(ft_atoi(lvl) + 1));
	else
		add_to_env("SHLVL","1");
}
