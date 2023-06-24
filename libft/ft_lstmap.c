/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 04:37:01 by srachdi           #+#    #+#             */
/*   Updated: 2022/10/25 15:42:18 by srachdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newhead;

	if (!lst || !f || !del)
		return (NULL);
	newhead = NULL;
	while (lst)
	{
		newlst = ft_lstnew (f (lst->content));
		if (!newlst)
		{
			ft_lstclear(&newhead, del);
			return (NULL);
		}
		ft_lstadd_back(&newhead, newlst);
		lst = lst->next;
	}
	return (newhead);
}
