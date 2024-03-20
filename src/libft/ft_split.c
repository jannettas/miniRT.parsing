/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:33:17 by zsoltani          #+#    #+#             */
/*   Updated: 2023/11/08 12:03:48 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#1.  The string to be split.
#2.  The delimiter character.

Return value: The array of new strings resulting from the split.
NULL if the allocation fails.

External functs. malloc, free

Description 
Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter.  The array must be
ended by a NULL pointer.
*/

static int	ft_count_words(const char *str, char c)
{
	int	i;
	int	words_counter;

	i = 0;
	words_counter = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			words_counter++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
	}
	return (words_counter);
}

static char	*ft_words(const char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (*str && *str == c)
		str++;
	while (str[i] && str[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_words(int i, char **ptr)
{
	while (i > 0)
	{
		free(ptr[i - 1]);
		i--;
	}
	free(ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr_words;
	int		words;
	int		i;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	ptr_words = malloc(sizeof(char *) * (words + 1));
	if (ptr_words == NULL)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s && *s == c)
			s++;
		ptr_words[i] = ft_words(s, c);
		if (ptr_words[i] == NULL)
			free_words(i, ptr_words);
		while (*s && *s != c)
			s++;
		i++;
	}
	ptr_words[i] = NULL;
	return (ptr_words);
}