/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 02:57:26 by srachdi           #+#    #+#             */
/*   Updated: 2022/11/11 01:02:42 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	nsize(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
	{
		n *= -1;
		count++;
	}
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	int		c;
	char	*str;

	c = nsize(n);
	str = malloc(sizeof(char) * (c + 1));
	if (!str)
		return (0);
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str[c] = '\0';
	if (n < 0)
	{
		str[0] = '-';
	}
	while (n != 0)
	{
		str[--c] = ft_abs (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
