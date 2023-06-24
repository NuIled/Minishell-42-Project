/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:37:03 by srachdi           #+#    #+#             */
/*   Updated: 2022/11/11 00:26:00 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	else if (dstsize < ft_strlen(dst))
		len = ft_strlen(src) + dstsize;
	else
		len = ft_strlen(src) + ft_strlen(dst);
	while (dst[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (len);
}
