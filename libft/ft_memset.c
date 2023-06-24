/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 06:12:47 by srachdi           #+#    #+#             */
/*   Updated: 2022/11/02 18:40:14 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = s;
	while (len--)
	{
		*ptr = (unsigned char)c;
		ptr++;
	}
	return (s);
}
