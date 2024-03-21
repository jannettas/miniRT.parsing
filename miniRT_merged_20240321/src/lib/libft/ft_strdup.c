/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:46:21 by zsoltani          #+#    #+#             */
/*   Updated: 2022/12/08 11:06:00 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*   
function allocates sufficient memory for a copy of the string s1, 
does the copy, 
and returns a pointer to it. 

If insufficient memory is available, NULL is returned 
and errno is set to ENOMEM.
*/
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
char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!ptr)
		return (0);
	while (*s1)
	{
		ptr[i] = *s1;
		i++;
		s1++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
int	main(void)
{
	char	string[20] = "HelloWorld";
	char	string2[10] = "";
	char	string3[10] = " ";

	printf("%s\n", ft_strdup(string));
	printf("%s\n", strdup(string));
	printf(":%s:\n", ft_strdup(string2));
	printf(":%s:\n", strdup(string2));
	printf(":%s:\n", ft_strdup(string3));
	printf(":%s:\n", strdup(string3));
	return (0);
}*/
