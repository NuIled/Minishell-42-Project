/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 04:24:52 by srachdi           #+#    #+#             */
/*   Updated: 2022/11/12 00:34:55 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nxt;

	if (!lst || !del || !*lst)
		return ;
	while (*lst != NULL)
	{
		nxt = (*lst)->next;
		del ((*lst)->content);
		free (*lst);
		*lst = nxt;
	}
	*lst = NULL;
}
