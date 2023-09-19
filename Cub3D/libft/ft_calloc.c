/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:48:48 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/24 14:45:06 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*o;

	if (nmemb > (SIZE_MAX / size))
		return (0);
	o = malloc(nmemb * size);
	if (o == NULL)
		return (0);
	ft_bzero(o, nmemb * size);
	return (o);
}
