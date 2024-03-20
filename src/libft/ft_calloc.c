/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:26:02 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/08 10:21:55 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
     The calloc() function contiguously allocates enough space for count
     objects that are size bytes of memory each and returns a pointer to the
     allocated memory.  The allocated memory is filled with bytes of value
     zero.*/
/*
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n > 0)
	{
		*ptr++ = '\0';
		n--;
	}
}
*/

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(size * count);
	if (!ptr)
		return (0);
	ft_bzero(ptr, size * count);
	return (ptr);
}

/*
int	main(void)
{
	int	*res;

	res = (int *) ft_calloc(1, sizeof(int));
	printf("%d\n", res[0]);
	printf("%d\n", res[1]);
	printf("%d\n", res[2]);
	printf("%d\n", res[3]);
	printf("%d\n", res[4]);
	printf("%d\n", res[5]);
	printf("%d\n", res[6]);
	printf("%d\n", res[7]);
	printf("%d\n", res[8]);
	printf("%d\n", res[9]);
	printf("%d\n", res[10]);
	return (0);
	
}*/
