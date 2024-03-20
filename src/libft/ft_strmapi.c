/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:27:35 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/09 19:29:18 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
s: The string on which to iterate.
f: The function to apply to each character.
Return value
The string created from the successive applications of ’f’.
Returns NULL if the allocation fails.
External functs: malloc
Description
Applies the function ’f’ to each character of the string ’s’,
and passing its index as first argument to create a new string 
(with malloc(3)) resulting from successive applications of ’f’.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	str = ft_strdup(s);
	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		str[i] = (*f)(i, str [i]);
		i++;
	}
	return (str);
}
