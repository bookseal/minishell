/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gichlee <gichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:34:14 by gichlee           #+#    #+#             */
/*   Updated: 2023/07/23 17:22:23 by gichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*ft_popline(char *buf)
{
	char	*line;
	int		idx;

	if (!buf || *buf == '\0')
		return (NULL);
	idx = 0;
	while (buf[idx] && buf[idx] != '\n')
		idx++;
	line = ft_calloc(idx + 2, sizeof(char));
	idx = 0;
	while (buf[idx] && buf[idx] != '\n')
	{
		line[idx] = buf[idx];
		idx++;
	}
	if (buf[idx] && buf[idx] == '\n')
		line[idx] = '\n';
	return (line);
}

char	*ft_cutbuf(char *buf)
{
	char	*new_buf;
	int		idx;
	int		j;

	idx = 0;
	while (buf[idx] && buf[idx] != '\n')
		idx++;
	if (buf[idx] == '\0')
	{
		free(buf);
		return (NULL);
	}
	new_buf = ft_calloc((ft_strlen(buf) - idx + 1), sizeof(char));
	idx++;
	j = 0;
	while (buf[idx + j] != '\0')
	{
		new_buf[j] = buf[idx + j];
		j++;
	}
	free(buf);
	return (new_buf);
}

char	*read_all(int fd, char *res)
{
	char	*buf;
	int		bytes_read;

	if (!res)
		res = ft_calloc(1, sizeof(char));
	buf = ft_calloc(1 + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, 1);
		if (bytes_read == -1)
		{
			free(buf);
			free(res);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		res = gnl_strjoin_free(res, buf);
		if (ft_strchr_i(res, '\n') != -1)
			break ;
	}
	free(buf);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0)
		return (NULL);
	buf = read_all(fd, buf);
	if (!buf)
		return (NULL);
	line = ft_popline(buf);
	buf = ft_cutbuf(buf);
	return (line);
}
