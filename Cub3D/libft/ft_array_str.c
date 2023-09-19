/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:07:27 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/24 09:53:08 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	astr_len(char **ss)
{
	int	n;

	if (!ss)
		return (0);
	n = 0;
	while (ss[n++])
		;
	return (n);
}

// Free array of strings
int	free_array_str(char ***ss1, int i)
{
	char	**ss0;
	char	**ss;

	if (!ss1)
		return (0);
	ss = *ss1;
	if (!ss)
		return (0);
	ss0 = ss;
	while (*ss)
		free(*(ss++));
	free(ss0);
	*ss1 = 0;
	return (i);
}

// Add back an element
char	**astr_addback(char **ss, char *s)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (astr_len(ss) + 2));
	if (!new)
		return (0);
	i = -1;
	if (ss)
		while (ss[++i])
			new[i] = ss[i];
	else
		i++;
	new[i] = s;
	new[++i] = 0;
	free(ss);
	return (new);
}

// Copy entire array
char	**astr_copy(char **ss)
{
	char	**new;
	int		i;

	if (!ss)
		return (0);
	new = malloc(sizeof(char *) * (astr_len(ss) + 1));
	if (!new)
		return (0);
	i = -1;
	while (ss[++i])
	{
		new[i] = ft_strdup(ss[i]);
		if (!new[i])
		{
			free_array_str(&new, 0);
			return (0);
		}
	}
	new[i] = 0;
	return (new);
}

// Remove an element
void	astr_remove(char **ss, void *dr, int (*cmp)(), void (*del)(void *))
{
	char	*s;
	int		i;

	if (!ss)
		return ;
	i = 0;
	while (ss[i])
	{
		if (!(*cmp)(ss[i], dr))
		{
			s = ss[i];
			while (ss[++i])
				ss[i - 1] = ss[i];
			del(s);
			ss[i - 1] = 0;
		}
		if (ss[i])
			i++;
	}
}
