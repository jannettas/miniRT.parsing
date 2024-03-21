/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:44:55 by zsoltani          #+#    #+#             */
/*   Updated: 2023/10/05 23:07:53 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_line(char *str)
{
	char	*line;
	int		len;
	int		i;
	int		n;

	if (!str || !*str)
		return (0);
	n = gnl_check_eol(str);
	len = gnl_strlen(str);
	if (n >= 0)
		line = gnl_calloc(sizeof(char) * (n + 2));
	else
		line = gnl_calloc(sizeof(char) * (len + 1));
	if (!line)
		return (0);
	i = 0;
	while (str[i])
	{
		line[i] = str[i];
		if (str[i] == '\n')
			break ;
		i++;
	}
	return (line);
}

char	*gnl_trim(char *str)
{
	int		start;
	int		len;
	char	*cpy;

	if (!str)
		return (0);
	if (*str == 0)
		return (gnl_free(str));
	start = gnl_check_eol(str) + 1;
	len = gnl_strlen(str);
	if (start >= 1 && (len - start) > 0)
		cpy = gnl_calloc(sizeof(char) * (len - start + 1));
	else
		return (gnl_free(str));
	if (!cpy)
		return (gnl_free(str));
	len = 0;
	while (str[start - 1])
		cpy[len++] = str[start++];
	free(str);
	return (cpy);
}

char	*gnl_join(char *str, char *buffer, int position)
{
	char	*cpy;
	int		len;
	int		i;
	int		j;

	if (position < 1)
		return (str);
	len = gnl_strlen(str) + position;
	cpy = gnl_calloc(len + 1);
	if (!cpy)
		return (str);
	i = 0;
	while (str[i])
	{
		cpy[i] = str[i];
		i++;
	}
	j = 0;
	while (len > i)
		cpy[i++] = buffer[j++];
	free(str);
	return (cpy);
}

char	*gnl_read(int fd, char *str)
{
	int		chars_read;
	char	*buffer;

	if (!str)
		str = gnl_calloc(1);
	if (!str)
		return (0);
	buffer = gnl_calloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (gnl_free(str));
	chars_read = BUFFER_SIZE;
	while (chars_read > 0)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read == -1)
		{
			free(buffer);
			return (gnl_free(str));
		}
		str = gnl_join(str, buffer, chars_read);
		if (gnl_check_eol(str) >= 0)
			break ;
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*nextline;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (0);
	str = gnl_read(fd, str);
	if (!str)
		return (0);
	nextline = gnl_line(str);
	str = gnl_trim(str);
	return (nextline);
}
