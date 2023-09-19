/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:52:53 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/16 15:08:15 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strcpy(char *s, int len)
{
	int		i;
	char	*s0;

	s0 = malloc(sizeof(char) * (len + 1));
	if (!s0)
		return (0);
	i = 0;
	while (s[i] && i < len)
	{
		s0[i] = s[i];
		i++;
	}
	s0[i] = 0;
	return (s0);
}

void	t_strlst_new(t_str_list **strs, char *s, int len)
{
	t_str_list	*new;
	t_str_list	*last;

	if (len <= 0)
		return ;
	new = malloc(sizeof(t_str_list));
	if (!new)
		return ;
	new->s = ft_strcpy(s, len);
	if (!new->s)
	{
		free(new);
		return ;
	}
	new->next = 0;
	if (*strs)
	{
		last = *strs;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*strs = new;
}

static int	strlst_size(t_str_list *strs)
{
	int			i;
	int			size;
	t_str_list	*lst;

	lst = strs;
	size = 0;
	while (lst)
	{
		i = -1;
		while (lst->s[++i])
			size++;
		lst = lst->next;
	}
	return (size);
}

static char	*strlst_str(t_str_list *strs)
{
	int			i;
	int			size;
	char		*s;
	t_str_list	*lst;

	if (!strs)
		return (0);
	size = strlst_size(strs);
	s = malloc(sizeof(char) * (size + 1));
	if (!s)
		return (0);
	lst = strs;
	size = 0;
	while (lst)
	{
		i = -1;
		while (lst->s[++i])
			s[size++] = lst->s[i];
		lst = lst->next;
	}
	s[size] = 0;
	return (s);
}

char	*get_strs(t_str_list *strs, char *buf, char *src, int start)
{
	int			i;
	char		*s;
	t_str_list	*lst;
	t_str_list	*next;

	if (*buf)
	{
		i = start - 1;
		while (src[++i])
			buf[i - start] = src[i];
		buf[i - start] = 0;
	}
	s = strlst_str(strs);
	lst = strs;
	while (lst)
	{
		next = lst->next;
		free(lst->s);
		free(lst);
		lst = 0;
		lst = next;
	}	
	return (s);
}
