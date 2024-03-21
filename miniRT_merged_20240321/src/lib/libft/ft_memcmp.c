/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:56:54 by zsoltani          #+#    #+#             */
/*   Updated: 2022/11/30 12:25:56 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *) s1;
	ptr2 = (unsigned char *) s2;
	while (n > 0)
	{
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		ptr1++;
		ptr2++;
		n--;
	}
	return (0);
}

/*int main(void)
{
    char a[15] = "Bonjour";
    char b[15] = "Bonjour";
    int res1;
    int res2;

    res1 = ft_memcmp(a, b, 6);
    res2 = memcmp(a, b, 6);
    printf("%d\n", res1);
    printf("%d\n", res2);
    return(0);
}*/
