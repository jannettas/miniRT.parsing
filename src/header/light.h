/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:31:25 by thibault          #+#    #+#             */
/*   Updated: 2024/03/20 21:13:01 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

typedef struct s_vec3 t_vec3;
typedef struct s_world t_world;
typedef struct s_param t_param;

typedef struct s_light
{
	t_vec3	position;
	double	brightness;
	t_color	intensity;
	int	in_shadow;
}	t_light;

typedef struct s_sight
{
	t_vec3	eyev;
	t_vec3	normalv;
}	t_sight;

t_color	lighting(t_shape *shape, t_light light, t_vec3 point, t_sight sight);
t_color	dark_exposure(t_material m, t_exposure e);
t_color	light_exposure(t_material m, t_light light,	t_exposure e, t_sight sight);
t_color	color_get_hit_color(t_world world, t_param param);


#endif