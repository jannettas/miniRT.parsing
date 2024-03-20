/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:29:09 by thibault          #+#    #+#             */
/*   Updated: 2024/03/18 15:12:48 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

typedef struct s_hit t_hit;
typedef struct s_world t_world;
typedef struct s_shape t_shape;

typedef struct s_ray
{
	t_vec3	direction;
	t_vec3	origin;
	t_hit	*hit_list;
}	t_ray;

/*ray_op.c*/
t_ray	ray_create(t_vec3 origin, t_vec3 direction);
t_vec3	ray_get_point(t_ray ray, double t);
t_ray	ray_transform(t_ray ray, t_matrix matrix);
void	ray_print(t_ray ray);

/*ray_hits.c*/
t_hit	*hit_new_intersection(double t, t_shape *shape);
t_hit	*hit_get_last(t_hit *hit);
int		ray_shape_intersection(t_hit **hit_list, t_shape *shape, t_ray ray);
void	hit_lst_print(t_hit *hit_list);
t_hit	*hit_get_closer_hit(t_hit *hit_list);
t_hit	*ray_intersection(t_world *world, t_ray ray);
#endif
