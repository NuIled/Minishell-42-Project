/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:36:04 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/04 23:06:25 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	**lst_to_arr_env(t_env *env)
{
	int		i;
	int		lst_size;
	char	**env_arr;
	t_env	*head;

	i = 0;
	lst_size = 0;
	head = env;
	lst_size = list_size(env) + 1;
	env_arr = malloc(sizeof(char *) * lst_size);
	if (!env_arr)
		return (NULL);
	while (head)
	{
		env_arr[i] = str_char_str(head->var, head->value, '=');
		i++;
		head = head->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

void	print_sorted_env(void)
{
	char	**env_arr;

	env_arr = lst_to_arr_env(g_vars->env);
	sort_env(env_arr);
	print_env(env_arr);
	free_array(env_arr);
}

int	is_env_updated(char *var, char *value, int mode)
{
	t_env	*head;

	head = g_vars->env;
	while (head)
	{
		if (!ft_strcmp(var, head->var))
		{
			if (mode == 1)
				update_env(var, value);
			else if (mode == 2)
				append_to_env(var, value);
			return (1);
		}
		head = head->next;
	}
	return (0);
}

void	export_var_value(char *arg)
{
	int		i;
	int		updated;
	char	*var;
	char	*value;

	var = get_var(arg);
	i = ft_strlen(var);
	value = get_value(arg, i);
	if (arg[i] == '\0')
		updated = 0;
	else if (arg[i] == '+')
		updated = is_env_updated(var, value, 2);
	else
		updated = is_env_updated(var, value, 1);
	if (!updated)
		add_to_env(var, value);
	g_vars->status = 0;
}

void	export(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	if (!cmd->argv[1])
		print_sorted_env();
	else
	{
		while (cmd->argv[i])
		{
			j = valid_export(cmd->argv[i]);
			if (j == -1)
			{
				ft_putstr_fd("minishell: export: ", STDERR_FILENO);
				ft_putstr_fd(cmd->argv[i], STDERR_FILENO);
				ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
				g_vars->status = 1;
			}
			else
				export_var_value(cmd->argv[i]);
			i++;
		}
	}
}
