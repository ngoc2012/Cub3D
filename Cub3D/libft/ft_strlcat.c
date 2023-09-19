/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 09:55:02 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/19 04:38:41 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	size_dst;
	size_t	size_src;

	if (!dest)
	{
		if (size > 0)
			size_dst = ft_strlen(dest);
		return (ft_strlen(src));
	}
	size_dst = ft_strlen(dest);
	if (size > size_dst)
		size_src = ft_strlcpy(&dest[size_dst], (char *) src, size - size_dst);
	else
		size_src = ft_strlen(src);
	if (size_dst < size)
		size = size_dst;
	return (size + size_src);
}
