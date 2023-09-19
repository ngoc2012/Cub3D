/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:56:59 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/19 04:50:13 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*o;

	o = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!o)
		return (0);
	return (ft_memcpy(o, src, ft_strlen(src) + 1));
}
