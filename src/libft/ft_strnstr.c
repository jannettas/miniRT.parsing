/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 00:24:33 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/07 20:19:18 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*if needle is empty string return haystack
if found return a pointer to the first char of the first occurence
if no needle in haystack return 0*/

/*
size_t  ft_strlen(const char *str)
{
	size_t  i;
	i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	nlen;
	char	*ptr;

	i = 0;
	ptr = (char *)haystack;
	nlen = ft_strlen(needle);
	if (*needle == 0)
		return (ptr);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] && haystack[i + j]
			&& haystack[i + j] == needle[j] && i + j < len)
			j++;
		if (j == nlen)
			return (ptr + i);
		i++;
	}
	return (0);
}

/*
int	main(void)
{
//	char	hay[20] = "HelloWorld!";
//	char	need[20] = "Hello";

	printf("%s\n", ft_strnstr("Hello", "e", 2));
	printf("%s\n", strnstr("Hello", "e", 2));
	printf("%p\n", ft_strnstr("Hello", "e", 2));
	printf("%p\n", strnstr("Hello", "e", 2));
	return (0);
}*/
