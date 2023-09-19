/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:11:40 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/22 07:54:56 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static int	pow_(int n)
{
	int	i;
	int	o;

	i = 0;
	o = 1;
	while (i++ < n)
		o *= (int) 10;
	return (o);
}

static int	get_len(long n)
{
	int	i;

	if (n < 0)
		n = -n;
	i = 0;
	while (n != 0)
	{
		n = (n - n % 10) / 10;
		i++;
	}
	return (i);
}

static void	get_num(long n, char *s, int len)
{
	int		i;
	char	*base;

	base = "0123456789";
	if (n < 0)
		n = -n;
	while (len)
	{
		i = n / pow_(len - 1);
		*s = base[i];
		n -= i * pow_(len - 1);
		len--;
		s++;
	}
	*s = 0;
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	char	*s;
	char	*s0;

	if (n == 0)
		return (ft_strdup("0"));
	len = get_len(n);
	i = len;
	if (n < 0)
		i++;
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (0);
	s0 = s;
	if (n < 0)
		*s++ = '-';
	get_num((long) n, s, len);
	return (s0);
}
