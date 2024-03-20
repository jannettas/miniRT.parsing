/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:33:50 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/23 00:37:17 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#1.  the integer to convert.
Return value The string representing the integer.  NULL if the
allocation fails.
External functs.malloc
Description Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.
*/

static int	ft_intlen(int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = nb * -1;
		i++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_intlen(n);
	n = (long)n;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		str[len--] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
/*
int	main(void)
{
	int	n;

	n = 123;
	printf("ft_itoa(%d) = %s\n", n, ft_itoa(n));
	n = -123;
	printf("ft_itoa(%d) = %s\n", n, ft_itoa(n));
	n = 0;
	printf("ft_itoa(%d) = %s\n", n, ft_itoa(n));
	n = INT_MAX;
	printf("ft_itoa(%d) = %s\n", n, ft_itoa(n));
	n = INT_MIN;
	printf("ft_itoa(%d) = %s\n", n, ft_itoa(n));
	return (0);
}
*/
