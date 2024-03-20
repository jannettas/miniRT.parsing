/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:03:06 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/08 23:12:58 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
appends string src to the end of dst.  

It will append at most dstsize - strlen(dst) - 1 characters.  

It will then NUL-terminate, unless  dstsize is 0 
or the original dst string was longer than dstsize 

If the src and dst strings overlap, the behavior is undefined.

strlcat() functions return the total length of the string they tried to create.
For strlcat() that means the initial length of dst plus the length of src.
*/
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
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	j;
	size_t	lendst;
	size_t	lensrc;

	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	j = 0;
	if (dstsize == 0)
		return (lensrc);
	if (dstsize > 0 && lendst < dstsize -1)
	{
		while (j < (dstsize - lendst - 1) && src[j])
		{
			dst[lendst + j] = src[j];
			j++;
		}
		dst[lendst + j] = '\0';
	}
	if (dstsize <= lendst)
		return (dstsize + lensrc);
	return (lendst + lensrc);
}
/*
int	main(void)
{
	char	a[20] = "Hello";
	char	b[20] = "Bonjour";
	char	c[20] = "Hello";
	char	d[20] = "Bonjour";
	int	res1;
	int	res2;

	res1 = ft_strlcat(a, b, 10);
	res2 = strlcat(c, d, 10);
	printf("%d\n", res1);
	printf("%d\n", res2);
	printf(":%s:\n", a);
	printf(":%s:\n", c);
	return (0);
}*/
