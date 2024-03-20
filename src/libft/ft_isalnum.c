/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:31:13 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/01 23:32:35 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (c < 48 || (c > 57 && c < 65) || (c > 90 && c < 97) || c > 122)
		return (0);
	return (1);
}

/*int main(void)
{
    char	a = 'A';
	char	b = '{';
	char	d = '%';
    char    e = '!';

	printf("%d\n", ft_isalnum(a));
	printf("%d\n", ft_isalnum(b));
	printf("%d\n", ft_isalnum(d));
    printf("%d\n", ft_isalnum(e));
	return (0);
}*/
