/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:54:26 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/09 16:22:10 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		*(char *)(dst + i) = *(char *)(src + i);
		i++;
	}
	return (dst);
}

/*
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*pdst;
	unsigned char	*psrc;

	pdst = (unsigned char *) dst;
	psrc = (unsigned char *) src;
	if ((src != (void *) 0) && (dst != (void *) 0))
	{
		while (n > 0)
		{
			*pdst = *psrc;
			pdst++;
			psrc++;
			n--;
		}
		return (dst);
	}
	return (0);
}
*/
/*
int main(void)
{
	char a[20] = "HelloBonjour";

	ft_memcpy(a + 5, a, 6);
	printf("%s\n", a);
	memcpy(a + 5, a, 6);
	printf("%s\n", a);
	return (0);
}*/
