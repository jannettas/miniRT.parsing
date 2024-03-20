/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:18:53 by zsoltani          #+#    #+#             */
/*   Updated: 2022/11/28 16:04:44 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

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
/*
int	main(void)
{
//	char	*str = "ABCD";
	char	*src = "ABCD";
	char	*str = malloc(sizeof(char) * 5);
	strcpy(str, src);

	ft_bzero(str, 3);
	return (0);
}*/
