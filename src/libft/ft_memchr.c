/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 00:02:57 by zsoltani          #+#    #+#             */
/*   Updated: 2022/11/30 12:23:41 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n > 0)
	{
		if (*ptr == (unsigned char) c)
			return (ptr);
		ptr++;
		n--;
	}
	return (0);
}

/*int	main(void)
{
	char	a[15] = "Hellohihihi";
	char	* res1;
	char 	* res2;
    
	res1 = memchr(a, 'o', 7);
	res2 = ft_memchr(a, 'o', 7);
	printf("%s\n", res1);
	printf("%s\n", res2);
	return (0);
}*/
