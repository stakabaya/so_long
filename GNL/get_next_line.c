/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 16:24:28 by stakabay          #+#    #+#             */
/*   Updated: 2021/11/25 09:35:06 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen_gnl(s);
	if (s_len < start)
		len = 0;
	else if (s_len - start < len)
		len = s_len - start;
	sub = malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	ft_memcpy_gnl(sub, s + start, len);
	*(sub + len) = '\0';
	return (sub);
}

int	fail(char **sta, char **buf)
{
	if (sta != NULL)
	{
		free(*sta);
		*sta = NULL;
	}
	if (buf != NULL)
	{
		free(*buf);
		*buf = NULL;
	}
	return (-1);
}

int	join_sta(char **sta, char *buf)
{
	char	*tmp;

	if (!*sta)
	{
		*sta = ft_strdup_gnl("");
		if (!*sta)
			return (0);
	}
	tmp = ft_strjoin_gnl(*sta, buf);
	if (!tmp)
		return (0);
	free(*sta);
	*sta = tmp;
	return (1);
}

int	join_line(char **line, char **sta, char *ptr)
{
	char	*tmp;

	*line = ft_substr_gnl(*sta, 0, ptr - *sta);
	if (!*line)
	{
		free(*sta);
		*sta = NULL;
		return (-1);
	}
	if (ptr == 0)
	{
		free(*sta);
		*sta = NULL;
		return (0);
	}
	tmp = ft_strdup_gnl(ptr + 1);
	if (!tmp)
	{
		free(*sta);
		*sta = NULL;
		return (-1);
	}
	free(*sta);
	*sta = tmp;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*sta[1024 + 1];
	char		*buf;
	char		*ptr;
	int			rc;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (fail(&sta[fd], &buf));
	rc = read(fd, buf, BUFFER_SIZE);
	while (rc >= 0)
	{
		buf[rc] = '\0';
		if (!(join_sta(&sta[fd], buf)))
			return (fail(&sta[fd], &buf));
		ptr = ft_strchr_gnl(sta[fd], '\n');
		if ((ptr != 0) || rc == 0)
		{
			free(buf);
			return (join_line(line, &sta[fd], ptr));
		}
		rc = read(fd, buf, BUFFER_SIZE);
	}
	return (fail(&buf, &sta[fd]));
}
