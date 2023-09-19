/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 06:41:32 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/08/10 12:48:39 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Add back with order
void	ft_lstadd_back2(t_list **lst, t_list *new, int (*cp)())
{
	t_list	*last;
	t_list	*cur;

	if (!*lst || !lst)
		*lst = new;
	else
	{
		cur = *lst;
		if (!(*cp)(cur->content, new->content))
		{
			*lst = new;
			new->next = cur;
			return ;
		}
		while (cur && (*cp)(cur->content, new->content))
		{
			last = cur;
			cur = cur->next;
		}
		last->next = new;
		new->next = cur;
	}
}
