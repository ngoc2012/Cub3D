/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:28:59 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/19 04:43:27 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;
	int	l;

	if (!big && len == 0)
		return (0);
	l = ft_strlen(little);
	if (l == 0)
		return ((char *) big);
	i = 0;
	while (((i < ((int) ft_strlen(big) - l + 1)
				&& i <= ((int) len - l)) || ((int) len < 0)) && big[i])
	{
		if (!ft_strncmp(&big[i], little, l))
			return ((char *) &(big[i]));
		i++;
	}
	return (0);
}
