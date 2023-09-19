/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:09:14 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/25 16:08:59 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*o;

	if (len == 0 || ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	o = malloc(sizeof(char) * (len + 1));
	if (!o)
		return (0);
	ft_strlcpy(o, (char *) &s[start], len + 1);
	return (o);
}
