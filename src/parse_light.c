/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:01:43 by zsoltani          #+#    #+#             */
/*   Updated: 2024/03/21 18:16:30 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_ambient_lightning(t_ambient *ambient, char **scene_values)
{
	char	**col;

	if (!ambient)
		return;
	col = ft_split(scene_values[2], ',');
	if (count_tokens(scene_values) != 3 || count_tokens(col) != 3)
	{
		perror("Correct format: A [color R,G,B]\n");
		exit(EXIT_FAILURE);
	}
	ambient->ratio = ft_atod(scene_values[1]);
	ambient->color = (t_color){ft_atod(col[0]), ft_atod(col[1]),
					ft_atod(col[2])};
	free_split(col);
}

// usage of light x y z, brightness range 0 to 1, rgb not used in mandatory part
void	add_light(t_light *light, char **scene_values)
{
	char	**coord;
	char	**color;

	coord = ft_split(scene_values[1], ',');
	color = ft_split(scene_values[3], ',');
	// while(*coord)
	// {
	// 	printf("coord: %s\n", *coord);
	// 	coord++;
	// }
	// while(*color)
	// {
	// 	printf("color: %s\n", *color);
	// 	color++;
	// }
	// printf("brightness (scene_values[2]): %s\n", scene_values[2]);
	// printf("nb of tokens: %d\n", count_tokens(scene_values));
	// printf("nb of coord: %d\n", count_tokens(coord));
	// printf("nb of color: %d\n", count_tokens(color));
	if (count_tokens(scene_values) != 4	|| count_tokens(coord) != 3
		|| count_tokens(color) != 3)
	{
		perror("Correct format: L [origin x,y,z] [brightness] [color R,G,B]\n");
		exit(EXIT_FAILURE);
	}
	light->position = (vec3_create)(ft_atod(coord[0]),
									ft_atod(coord[1]),
									ft_atod(coord[2]), 1);
	light->brightness = ft_atod(scene_values[2]);
	light->intensity = (t_color){ft_atod(color[0]),
								ft_atod(color[1]),
								ft_atod(color[2])};
	free_split(coord);
    free_split(color);
	//light->position = (vec3_create)(-10, 10, -10, 1);
	// light->position = (vec3_create)(0, 0.25, 0, 1);
	//light->intensity = (t_color){1, 1, 1};

	//TEST 1 et 2
		// scene->light.position = (vec3_create)(0, 0, -10, 1);
		// scene->light.intensity= (t_color){1, 1, 1};
	//TEST 3 et 4
		// scene->light.position = (vec3_create)(0, 10, -10, 1);
		// scene->light.intensity= (t_color){1, 1, 1};
	//TEST 5
		// scene->light.position = (vec3_create)(0, 0, 10, 1);
		// scene->light.intensity= (t_color){1, 1, 1};
}

//TO DELETE
// void	add_light_2(t_light *light, char *line)
// {
// 	(void)line;
// 	if(!light)
// 		return ;
// 	light->position = (vec3_create)(0, 0, 10, 1);
// 		// light->position = (vec3_create)(0, 0.25, 0, 1);
// 	// light->intensity = (t_color){1, 1, 1};
// 	light->intensity = (t_color){1, 1, 1};
// }