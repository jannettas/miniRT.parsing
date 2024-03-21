/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:08:52 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/01 23:28:49 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*int main(void)
{
    char    a = 'A';
    char    b = 127;
    char    d = '%';
    char    e = '?';

    printf("%d\n", ft_isascii(a));
    printf("%d\n", ft_isascii(b));
    printf("%d\n", ft_isascii(d));
    printf("%d\n", ft_isascii(e));
}*/
