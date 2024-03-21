/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:41:21 by zsoltani          #+#    #+#             */
/*   Updated: 2024/03/21 19:08:11 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_scn	t_scn;

// parser_utils.c
void	check_fd(int fd);
int		check_line(char *line);
int		allowed_chars(char c);
int		ft_check_extension(const char *s1, const char *s2, size_t n);
double	ft_atod(const char *str);

// parser_utils_2.c
int		count_tokens(char **token_list);
void	free_split(char **split);
int		check_sphere(char **scene_values, char **coord, char **col);
int		check_plane(char **scene_values, char **coord, char **norm, char **col);
int		check_cylinder(char **scene_values, char **coord, char **norm, char **col);

// parse_scene.c
int		parse_and_check_scene(char *scene_file, t_canevas *canevas, t_scn *scene);
int		check_scene(char *scene_file);
void	count_shapes_lights(char *scene_file, t_scn *scene);
void	parse_scene(char *scene_file, t_canevas *cnv, t_scn *scene);

// parse_shapes.c
void	add_shape_plane(t_shape *shape_elem, char **scene_values);
void	add_shape_cylinder(t_shape *shape_elem, char **scene_values);
void	add_shape_sphere(t_shape *shape_elem, char **scene_values);

// parse_light.c
void	add_ambient_lightning(t_ambient *ambient, char **scene_values);
void	add_light(t_light *light, char **scene_values);

#endif