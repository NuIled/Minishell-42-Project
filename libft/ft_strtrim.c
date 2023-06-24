/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 01:45:28 by srachdi           #+#    #+#             */
/*   Updated: 2022/10/24 02:44:03 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*str;

	i = 0;
	start = 0;
	if (!s1)
		return (0);
	end = ft_strlen(s1);
	while (s1[start] && is_set(s1[start], set))
		start++;
	while (end > start && is_set(s1[end - 1], set))
		end--;
	str = (char *)malloc (sizeof (char) * (end - start + 1));
	if (!str)
		return (NULL);
	while (end > start)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
