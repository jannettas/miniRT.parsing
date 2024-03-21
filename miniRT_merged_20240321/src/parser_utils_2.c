/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:49:01 by zsoltani          #+#    #+#             */
/*   Updated: 2024/03/21 18:57:15 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		count_tokens(char **token_list)
{
	int	i;

	i = 0;
	while (token_list[i])
		i++;
	return (i);
}

void free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	check_plane(char **scene_values, char **coord, char **norm, char **col)
{
if (count_tokens(scene_values) != 4	|| count_tokens(coord) != 3
		|| count_tokens(norm) != 3 || count_tokens(col) != 3)
	{
		perror("Correct format: pl [point x,y,z][normal x,y,z][color R,G,B]\n");
		exit(EXIT_FAILURE);
	}
	return (1);
}

int check_cylinder(char **scene_values, char **coord, char **norm, char **col)
{
	if (count_tokens(scene_values) != 6 || count_tokens(coord) != 3
		|| count_tokens(norm) != 3 || count_tokens(col) != 3)
	{
		perror("Format: cy [point x,y,z][normal x,y,z][diameter][height][color R,G,B]\n");
		exit(EXIT_FAILURE);
	}
	return (1);
}

int check_sphere(char **scene_values, char **coord, char **col)
{
	if (count_tokens(scene_values) != 4 || count_tokens(coord) != 3
		|| count_tokens(col) != 3)
	{
		perror("Correct format: sp [origin x,y,z] [diameter] [color R,G,B]\n");
		exit(EXIT_FAILURE);
	}
	return (1);
}
