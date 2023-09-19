/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:52:53 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/15 12:52:51 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static int	newline_pos(char *s)
{
	int	pos;

	pos = 0;
	while (s[pos] && s[pos] != '\n')
		pos++;
	if (pos == 0 && s[pos] != '\n')
		return (-1);
	if (s[pos] == '\n')
		return (pos);
	else
		return (-1);
}

static char	*get_container_line_con(char *con, char *buf, t_str_list *strs,
		t_containter c)
{
	while (c.ret)
	{
		if (c.icon + BUFFER_SIZE > CONTAINER_SIZE)
		{
			t_strlst_new(&strs, con, c.icon);
			c.icon = 0;
		}
		c.ret = read(c.fd, &con[c.icon], BUFFER_SIZE);
		if (c.ret == -1)
			return (0);
		if (c.ret)
		{
			con[c.icon + c.ret] = 0;
			c.pos = newline_pos(&con[c.icon]);
			if (c.pos != -1)
			{
				t_strlst_new(&strs, con, c.icon + c.pos + 1);
				return (get_strs(strs, buf, &con[c.icon], c.pos + 1));
			}
			c.icon += c.ret;
		}
		else
			t_strlst_new(&strs, con, c.icon + c.ret);
	}
	return (get_strs(strs, buf, con, c.pos + 1));
}

static char	*get_next_line_buf(int fd, char *buf, t_str_list *strs, int pos)
{
	int		ret;

	ret = 1;
	while (ret && pos == -1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (0);
		buf[ret] = 0;
		if (ret)
		{
			pos = newline_pos(buf);
			if (pos == -1)
			{
				t_strlst_new(&strs, buf, ret);
				if (ret < BUFFER_SIZE)
					return (get_strs(strs, buf, buf, ret));
				else
					buf[0] = 0;
			}
			else
				t_strlst_new(&strs, buf, pos + 1);
		}
	}
	return (get_strs(strs, buf, buf, pos + 1));
}

static char	*get_line(int fd, char *buf, int pos, t_str_list *strs)
{
	t_containter	c;
	char			con[CONTAINER_SIZE + 1];
	char			*b;

	c.fd = fd;
	c.ret = 1;
	c.icon = 0;
	c.pos = pos;
	c.size = BUFFER_SIZE;
	if (CONTAINER_SIZE > 10 * BUFFER_SIZE)
		b = &con[0];
	else
		b = &buf[0];
	if (CONTAINER_SIZE > 10 * BUFFER_SIZE)
		return (get_container_line_con(b, buf, strs, c));
	return (get_next_line_buf(fd, buf, strs, pos));
}

char	*get_next_line(int fd)
{
	int			pos;
	static char	buf[BUFFER_SIZE + 1];
	t_str_list	*strs;	

	pos = -1;
	strs = 0;
	if (*buf)
	{
		pos = newline_pos(buf);
		if (pos == -1)
		{
			t_strlst_new(&strs, buf, BUFFER_SIZE);
			buf[0] = 0;
		}
		else
		{
			t_strlst_new(&strs, buf, pos + 1);
			return (get_strs(strs, buf, buf, pos + 1));
		}
	}
	return (get_line(fd, buf, pos, strs));
}
