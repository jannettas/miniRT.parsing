/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:06:44 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/08 11:57:57 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

// strlcpy() copies up to dstsize - 1 characters from the string src to dst, 
// NUL- terminating the result if dstsize is not 0.
// the strlcpy() and strlcat() functions return the total 
//length of the string they tried to create.  
// For strlcpy() that means the length of src.
// If the return value is >= dstsize, the output string has been truncated.  
// It is the caller's responsibility to handle this.

#include "libft.h"
/*
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}
/*
int main(void)
{
    char s[15] = "Hello";
    char d[15] = "";
    int res1;
    int res2;
    
    printf(":%s\n", d);
    res1 = ft_strlcpy(d, s, 2);
    res2 = strlcpy(d, s, 2);
    printf("%d\n", res1);
    printf("%d\n", res2);
    printf("%lu\n", strlen(d));
    printf(":%s\n", d);
    return (0);
}*/
