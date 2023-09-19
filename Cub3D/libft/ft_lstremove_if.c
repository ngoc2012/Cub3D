/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:33:52 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/05 18:13:19 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstremove_if(t_list **bl, void *dr, int (*cp)(), void (*dl)(void *))
{
	t_list	*remove;
	t_list	*cur;

	if (!bl || !(*bl))
		return ;
	cur = *bl;
	while (cur && !(*cp)(cur->content, dr))
	{
		remove = cur;
		cur = remove->next;
		dl(remove->content);
		free(remove);
	}
	*bl = cur;
	while (cur)
	{
		if (cur->next && !(*cp)(cur->next->content, dr))
		{
			remove = cur->next;
			cur->next = remove->next;
			dl(remove->content);
			free(remove);
		}
		cur = cur->next;
	}
}
