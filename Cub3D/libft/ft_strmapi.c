/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:23:27 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/14 12:40:52 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*o;

	o = ft_strdup(s);
	if (!o)
		return (0);
	i = 0;
	while (o[i])
	{
		o[i] = f(i, o[i]);
		i++;
	}
	return (o);
}
