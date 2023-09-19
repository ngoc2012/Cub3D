/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 09:55:02 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/24 14:36:47 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	size_src;

	size_src = ft_strlen(src);
	if ((!dest) || (!src) || (size == 0))
		return (size_src);
	if (size_src > (size - 1))
	{
		ft_memcpy(dest, src, size - 1);
		dest[size - 1] = 0;
	}
	else
		ft_memcpy(dest, src, size_src + 1);
	return (size_src);
}
