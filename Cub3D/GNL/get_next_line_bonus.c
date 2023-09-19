/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:52:53 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/17 11:16:00 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_fd	*get_fd(int fd, t_fd *fdl, char *buf)
{
	int			i;
	t_fd		*f;

	f = 0;
	i = -1;
	while (++i < 1024 && fdl[i].buf)
		if (fd == fdl[i].fd)
			f = &fdl[i];
	if (!f)
	{
		f = &fdl[i];
		f->fd = fd;
		f->bs = 0;
	}
	if (f->bs > 0)
	{
		ft_memcpy(buf, f->buf, ft_strlen(f->buf) + 1);
		free(f->buf);
		f->bs = 0;
	}
	return (f);
}

static int	get_next_line_con(int fd, char *buf, char **s, int *pos)
{
	char		con[CONTAINER_SIZE + 1];
	int			icon;
	int			ret;

	icon = 0;
	con[0] = 0;
	ret = 1;
	while (ret && (icon + BUFFER_SIZE) < CONTAINER_SIZE)
	{
		ret = read(fd, &con[icon], BUFFER_SIZE);
		if (ret == -1)
			return (-1);
		icon += ret;
	}
	con[icon] = 0;
	*pos = get_line(buf, con, s);
	return (ret);
}

static int	get_next_line_buf(int fd, char *buf, char **s, int *pos)
{
	int			ret;

	ret = read(fd, buf, BUFFER_SIZE);
	if (ret == -1)
		return (-1);
	buf[ret] = 0;
	*pos = get_line(buf, buf, s);
	return (ret);
}

static char	*get_next_line_all(int fd, char *buf, char **s, t_fd *f)
{
	int			ret;
	int			pos;

	ret = 1;
	while (ret)
	{
		if (CONTAINER_SIZE > 10 * BUFFER_SIZE)
			ret = get_next_line_con(fd, buf, s, &pos);
		else
			ret = get_next_line_buf(fd, buf, s, &pos);
		if (ret == -1)
		{
			free(buf);
			free(*s);
			return (0);
		}
		if (pos != -1)
			return (get_out_put(*s, buf, f));
	}
	return (get_out_put(*s, buf, f));
}

char	*get_next_line(int fd)
{
	static t_fd	fdl[1024];
	t_fd		*f;
	char		*s;	
	char		*buf;

	if (CONTAINER_SIZE > 10 * BUFFER_SIZE)
		buf = malloc(sizeof(char) * (CONTAINER_SIZE + 1));
	else
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	buf[0] = 0;
	s = malloc(sizeof(char));
	if (!s)
		return (0);
	s[0] = 0;
	f = get_fd(fd, fdl, buf);
	if (*buf)
	{
		if (get_line(buf, buf, &s) != -1)
			return (get_out_put(s, buf, f));
	}
	return (get_next_line_all(fd, buf, &s, f));
}
