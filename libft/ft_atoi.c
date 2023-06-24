/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:58:16 by srachdi           #+#    #+#             */
/*   Updated: 2022/10/31 09:51:52 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n'
		|| c == '\f' || c == '\t'
		|| c == '\r' || c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	sum;

	sign = 1;
	sum = 0;
	while (ft_isspace (*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		sum = sum * 10 + (*str - 48);
		str++;
	}
	return (sum * sign);
}
