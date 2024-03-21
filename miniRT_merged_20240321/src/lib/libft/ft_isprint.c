/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:21:34 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/01 23:31:02 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	return (0);
}

/*int main(void)
{
    char    a = 'a';
    char    b = 32;
    char    d = 126;
    char    e = ' ';

    printf("%d\n", ft_isprint(a));
    printf("%d\n", ft_isprint(b));
    printf("%d\n", ft_isprint(d));
    printf("%d\n", ft_isprint(e));
}*/
