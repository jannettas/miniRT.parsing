/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:06:01 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/02 00:51:43 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char) c)
		return ((char *)s + i);
	return (0);
}
/*
int main(void)
{
	char	a[20] = "";
	char	* res1;
	char	* res2;

	res1 = ft_strchr(a, '\0');
	printf("%s\n", res1);
	res2 = strchr(a, '\0');
	printf("%s\n", res2);
	return (0);
}*/
