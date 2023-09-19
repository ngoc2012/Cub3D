/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:08:55 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/24 14:56:05 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*prev;
	t_list	*new;

	begin = 0;
	while (lst)
	{
		new = malloc(sizeof(t_list));
		if (!new)
		{
			if (begin)
				ft_lstclear(&begin, del);
			return (0);
		}
		new->content = f(lst->content);
		new->next = 0;
		if (begin)
			prev->next = new;
		else
			begin = new;
		prev = new;
		lst = lst->next;
	}
	return (begin);
}
