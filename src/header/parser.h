/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:41:21 by zsoltani          #+#    #+#             */
/*   Updated: 2024/03/21 00:09:36 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

void	check_fd(int fd);
int		check_line(char *line);
int		allowed_chars(char c);
int		ft_check_extension(const char *s1, const char *s2, size_t n);
double	ft_atod(const char *str);

// parser_2.c
int		count_tokens(char **token_list);
void	free_split(char **split);
// char	**ft_split_space(char const *s, char c);
// size_t	count_tokens(char const *s, char c);
// int		fill(char **tokens_array, char const *s, char c);
// int		safe_malloc(char **tokens_array, int position, size_t buffer);
// char	*ft_strncpy(char *s1, const char *s2, int n);

#endif