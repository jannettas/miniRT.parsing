/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:51:42 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/22 20:58:11 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
*/

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n >= 0 && n <= 9)
		ft_putchar_fd((n + 48), fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd((n * (-1)), fd);
	}
	else
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putnbr_fd((n % 10), fd);
	}
}
/*
int	main(void)
{
	ft_putnbr_fd(-2147483648, 1);
}
*/
