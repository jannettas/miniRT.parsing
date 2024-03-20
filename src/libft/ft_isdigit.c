/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:56:04 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/01 23:27:16 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

/*int main()
{
    char a = '1';
    char b = 'a';
    char d = ' ';

    printf("%d\n", ft_isdigit(a));
    printf("%d\n", ft_isdigit(b));
    printf("%d\n", ft_isdigit(d));
}*/
