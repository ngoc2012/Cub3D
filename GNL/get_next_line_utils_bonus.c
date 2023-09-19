/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:52:53 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/17 08:35:35 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	newline_pos(char *s)
{
	int	pos;

	pos = 0;
	if (!*s)
		return (-1);
	while (s[pos] && s[pos] != '\n')
		pos++;
	if (pos == 0 && s[pos] != '\n')
		return (-1);
	if (s[pos] == '\n')
		return (pos);
	else
		return (-1);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if ((!dest) && (!src))
		return (dest);
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

int	get_line(char *buf, char *con, char **s)
{
	char	*new;
	int		pos;
	int		ls;
	int		lc;
	int		lc1;

	if (!*con)
		return (-1);
	ls = ft_strlen(*s);
	lc = ft_strlen(con);
	pos = newline_pos(con);
	lc1 = lc;
	if (pos != -1)
		lc1 = pos + 1;
	new = malloc(sizeof(char) * (ls + lc1 + 1));
	ft_memcpy(new, *s, ls);
	ft_memcpy(&new[ls], con, lc1);
	new[ls + lc1] = 0;
	free(*s);
	*s = new;
	if (pos == -1)
		buf[0] = 0;
	else
		ft_memcpy(buf, &con[pos + 1], lc - pos);
	return (pos);
}

char	*get_out_put(char *s, char *buf, t_fd *f)
{
	if (*buf)
	{
		f->bs = ft_strlen(buf);
		f->buf = malloc(sizeof(char) * (ft_strlen(buf) + 1));
		ft_memcpy(f->buf, buf, ft_strlen(buf) + 1);
	}
	else
		f->bs = 0;
	free(buf);
	if (*s)
		return (s);
	free(s);
	return (0);
}
