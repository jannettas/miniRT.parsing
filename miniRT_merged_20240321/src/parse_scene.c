/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:28:24 by zsoltani          #+#    #+#             */
/*   Updated: 2024/03/23 13:18:19 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_and_check_scene(char *scene_file, t_canevas *cnv, t_scn *scene) // if ok returns 0
{
	if (check_scene(scene_file) == 0) //== OK -> init scene struct
		init_scene(scene_file, cnv, scene);
	else
		return (1);
	return (0);
}

int	check_scene(char *scene_file) // if ok returns 0
{
	int		fd;
	char	*line;
	fd = open(scene_file, O_RDONLY);

	check_fd(fd);
	line = get_next_line(fd);
	while (line)
	{
		if (check_line(line) == 0)
		{
			perror("Error: Scene file is not well formated\n");
			exit(EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	count_shapes_lights(char *scene_file, t_scn *scene)
{
	int		fd;
	char	*line;
	char	**scene_values;

	fd = open(scene_file, O_RDONLY);
	check_fd(fd);
	line = get_next_line(fd);
	while(line)
	{
		scene_values = ft_split(line, ' ');
		if (ft_strncmp(scene_values[0], "L", 1) == 0)
		{
			scene->world.nb_light += 1;
			//printf("nb_light: %d\n", scene->world.nb_light);
		}
		else if (ft_strncmp(scene_values[0], "sp", 2) == 0
				|| ft_strncmp(scene_values[0], "pl", 2) == 0
				|| ft_strncmp(scene_values[0], "cy", 2) == 0)
		{
			scene->world.nb_shape += 1;
			//printf("nb_shape: %d\n", scene->world.nb_shape);
		}
		free(scene_values);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

//void	parse_scene(char *scene_file, t_scn *scene)
void	parse_scene(char *scene_file, t_canevas *cnv, t_scn *scene) //when used with init_camera
{
	int		fd;
	char	*line;
	char	**scene_values;

	fd = open(scene_file, O_RDONLY);
	line = get_next_line(fd);
	while(line)
	{
		scene_values = ft_split(line, ' ');
		if (ft_strncmp(scene_values[0], "L", 1) == 0)
		{
			add_light(scene->world.light_tab++, scene_values);
			printf("light_tab: %p\n", scene->world.light_tab);
		}
		else if (ft_strncmp(scene_values[0], "C", 1) == 0)
			scene->camera = init_camera(cnv, scene_values);

		else if (ft_strncmp(scene_values[0], "A", 1) == 0)
			;//add_ambient_lightning(scene->world, scene_values); // to decide where do we put it in the struct
		else if (ft_strncmp(scene_values[0], "sp", 2) == 0)
		{
			add_shape_sphere(scene->world.shape_tab++, scene_values);
			//printf("shape_tab_sphere: %p\n", scene->world.shape_tab);
			//printf("radius: %.2f\n", scene->world.shape_tab->sphere.radius);
			//scene->world.shape_tab++;
		}
		else if (ft_strncmp(scene_values[0], "pl", 2) == 0)
		{
			add_shape_plane(scene->world.shape_tab++, scene_values);
			printf("shape_tab_plane: %p\n", scene->world.shape_tab);
		}
		else if (ft_strncmp(scene_values[0], "cy", 2) == 0)
		{
			add_shape_cylinder(scene->world.shape_tab++, scene_values);
			printf("shape_tab_cylindre: %p\n", scene->world.shape_tab);
		}
		free(scene_values);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
