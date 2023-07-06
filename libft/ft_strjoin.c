/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:40:58 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/05 20:30:31 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	char	*tmp;
	size_t	l;

	if (!s1 || !s2)
		return (0);
	l = ft_strlen(s1) + ft_strlen(s2) + 1;
	s = (char *)malloc (l * sizeof (char));
	if (!s)
		return (0);
	tmp = s;
	while (*s1)
	{
		*s = *s1;
		s++;
		s1++;
	}
	while (*s2)
	{
		*s = *s2;
		s++;
		s2++;
	}
	*s = '\0';
	return (tmp);
}
