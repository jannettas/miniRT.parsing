/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:34:29 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/08 11:15:47 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
int main(void)
{
	char	*str = "ABCDE";
//char    b[] = "abcd1";

	printf("%zu\n", ft_strlen(str));
//printf("%d\n", ft_strlen(b));
	printf("%zu\n", strlen(str));
	return (0);
}*/
