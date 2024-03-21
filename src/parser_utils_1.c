/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:39:12 by zsoltani          #+#    #+#             */
/*   Updated: 2024/03/21 18:27:34 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_check_extension(const char *s1, const char *s2, size_t n)
{
	if (s1 == NULL || s2 == NULL || n <= 0)
		return (1);
	while (*s1)
		s1++;
	while (*s2)
		s2++;
	while ((n > 0) && (*s1 == *s2))
	{
		s1--;
		s2--;
		n--;
	}
	if (n == 0 && *s1)
		return (0);
	else
		return (1);
}

void	check_fd(int fd)
{
	if (fd < 0)
	{
		perror("Error: File descriptor error\n");
		exit(EXIT_FAILURE);
	}
}

int	allowed_chars(char c)
{
	if ((c >= '0' && c <= '9') || c == '-' || c == '.' || c == ','
		|| c == '\t' || c == ' ' | c == '\n')
		return (1);
	return (0);
}

int	check_line(char *line)
{
	int	i;

	if (!line)
	{
		perror("Error: Error reading file,empty line\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == 'A' || line[i] == 'C' || line[i] == 'L')
			i++;
		if ((line[i] == 's' && line[i + 1] == 'p')
			|| (line[i] == 'c' && line[i + 1] == 'y')
			|| (line[i] == 'p' && line[i + 1] == 'l'))
			i += 2;
		if (allowed_chars(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

double	ft_atod(const char *str)
{
	int		i;
	int		sign;
	double	res;
	double	f;

	if (!str)
		return (0);
	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	if (str[i] == '.')
	{
		i++;
		f = 1;
		while (str[i] >= '0' && str[i] <= '9')
		{
			f /= 10;
			res = res + (str[i++] - '0') * f;
		}
	}
	return (res * sign);
}
