/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:06:56 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/23 00:34:20 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
*/

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (*(s + i) == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (0);
}

/*
int	main(void)
{
	char	a[20] = "";
	char	b[20] = "";
	char	*res1;
	char	*res2;

	res1 = ft_strrchr(a, '\0');
	printf(":%s:\n", res1);
	res2 = strrchr(b, '\0');
	printf(":%s:\n", res2);
	return (0);
}*/
