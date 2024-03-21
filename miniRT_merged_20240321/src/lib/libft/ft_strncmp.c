/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 23:14:36 by zsoltani          #+#    #+#             */
/*   Updated: 2022/11/30 12:17:58 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *) s1;
	ptr2 = (unsigned char *) s2;
	while ((n > 0) && (*ptr1 || *ptr2))
	{
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		ptr1++;
		ptr2++;
		n--;
	}
	return (0);
}
/*
int	main(void)
{
	char	a[15] = "Hello";
	char	b[15] = "Helloworld";
	int	res1;
	int	res2;

	res1 = ft_strncmp(a, b, 8);
	printf("%d\n", res1);
	res2 = strncmp(a, b, 8);
	printf("%d\n", res2);
	return(0);
}*/
