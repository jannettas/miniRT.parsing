/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:32:04 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/16 21:20:52 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
s1: The prefix string.
s2: The suffix string.

Return value The new string.
NULL if the allocation fails.

External finctions : malloc

Description
Allocates (with malloc(3)) and returns a new string, 
which is the result of the concatenation of ’s1’ and ’s2’.
*/
/*
size_t	ft_strlen(const char  *s) 
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lens1;
	size_t	lens2;
	size_t	i;
	size_t	j;
	char	*str;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(*s1) * (lens1 + lens2 + 1));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str [j++] = s2[i++];
	}
	str[j] = 0;
	return (str);
}
/*
int	main(void)
{
	char	a[20] = "Hello";
	char	b[20] = "Bonjour";

	printf("%s\n", ft_strjoin(a, b));
	return (0);
}
*/
