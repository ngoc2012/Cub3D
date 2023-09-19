/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:25:20 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/17 12:18:23 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s0;

	s0 = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (s0[i] == (unsigned char) c)
			return (&(s0[i]));
		i++;
	}
	return (0);
}
