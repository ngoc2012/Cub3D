/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 08:45:31 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/05/15 21:37:30 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

// Get number of strings at the out put, must be 0 if all match
static int	get_n_strs(const char *str, char charset)
{
	int	i;
	int	n_strs;

	i = 0;
	n_strs = 0;
	while (str[i])
	{
		while (str[i] && str[i] == charset)
			i++;
		if (str[i])
			n_strs++;
		while (str[i] && !(str[i] == charset))
			i++;
	}
	return (n_strs);
}

// Get chunks (begin and end) of string to output
static int	get_strs(const char *str, char charset, char **out)
{
	int		i;
	int		start;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == charset)
			i++;
		start = i;
		while (str[i] && !(str[i] == charset))
			i++;
		if (i > start)
		{
			out[j] = malloc(sizeof(char) * (i - start + 1));
			if (!out[j])
				return (0);
			ft_strlcpy(out[j], &(str[start]), i - start + 1);
			j++;
		}
	}
	return (1);
}

char	**ft_split(const char *str, char charset)
{
	int		n_strs;
	char	**out;
	char	**out0;

	n_strs = get_n_strs(str, charset);
	out = malloc(sizeof(char *) * (n_strs + 1));
	if (!out)
		return (0);
	if (n_strs > 0)
	{
		if (!get_strs(str, charset, out))
		{
			out0 = out;
			while (*out)
				free(*(out++));
			free(out0);
			return (0);
		}
	}
	out[n_strs] = 0;
	return (out);
}
