/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:25:56 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/17 12:09:27 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*pdst;
	unsigned char	*psrc;
	size_t			i;

	i = 0;
	pdst = (unsigned char *) dst;
	psrc = (unsigned char *) src;
	if (dst == NULL && src == NULL)
		return (0);
	else if (psrc < pdst)
	{
		while (len > 0)
		{
			pdst[len - 1] = psrc[len - 1];
			len--;
		}
	}
	while (i < len)
	{
		pdst[i] = psrc[i];
		i++;
	}
	return (dst);
}

/*
int	main(void)
{
	char	a[15] = "123456789";
	char	b[15] = "HelloBonjour";
	
	ft_memmove(a + 1, a, 7);
	printf("%s\n", a);
	ft_memmove(b + 5, a, 3);
	printf("%s\n", b);
	return (0);
}*/
