/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 10:01:44 by zsoltani          #+#    #+#             */
/*   Updated: 2023/10/05 23:08:02 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnl_calloc(int len)
{
	char	*ptr;
	int		i;

	i = 0;
	if (len < 1)
		return (0);
	ptr = malloc(len);
	if (!ptr)
		return (0);
	while (i < len)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*gnl_free(char *str)
{
	free(str);
	return (0);
}

int	gnl_check_eol(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (-1);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (i);
	return (-1);
}
