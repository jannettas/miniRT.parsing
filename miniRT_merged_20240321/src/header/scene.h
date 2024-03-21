/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:31:25 by thibault          #+#    #+#             */
/*   Updated: 2024/03/21 21:29:33 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef struct s_world t_world;

typedef struct s_scn
{
	t_cam	camera;
	t_world	world;
}	t_scn;

int		init_scene(char *scene_file, t_canevas *cnv, t_scn *scn);
int		parse_and_check_scene(char *scene_file, t_canevas *canevas, t_scn *scene);
t_shape	*create_shape_tab(int nb_shape);
t_light	*create_light_tab(int nb_light);
// void	add_shape_sphere(t_shape *shape_tab, char *line);
// void	add_shape_sphere_r05(t_shape *shape_tab, char *line); // to delete at the end
// void	add_light(t_light *light, char *line);
// void	add_light_2(t_light *light, char *line); //to delete at the end

#endif