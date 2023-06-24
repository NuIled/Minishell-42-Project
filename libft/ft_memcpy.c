/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 06:22:03 by srachdi           #+#    #+#             */
/*   Updated: 2022/10/24 05:40:17 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t	index;

	index = -1;
	if (dst == src || !n)
		return (dst);
	while (++index < n)
		*(char *)(dst + index) = *(char *)(src + index);
	return (dst);
}
