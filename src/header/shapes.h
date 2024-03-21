/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:02:42 by thibault          #+#    #+#             */
/*   Updated: 2024/03/21 15:41:45 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SHAPES_H
# define SHAPES_H

typedef struct s_material t_material;
typedef struct s_sight t_sight;

# define EPSILON		0.00001

typedef struct s_sphere
{
	double	radius;
	t_vec3	origin;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	origin;
	t_vec3	normal;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	origin;
	t_vec3	normal;
	double	radius;
	double	height;
}	t_cylinder;

typedef struct s_discriminant
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
	double	discr;
}	t_discriminant;

typedef struct s_shape
{
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		// t_cone		cone;
	};
	
	int				type_of_shape;
	t_matrix		transform;
	t_matrix		inverse;
	t_matrix		transpose;
	t_material		material;
	// t_hit_list	intersect;
	// t_normal_at		normal_at;
	t_vec3			normal_at;
	// t_checker		checker;
	// t_uv_map		map;
}	t_shape;

typedef struct s_hit
{
	double	t;
	t_shape	*object;
	t_hit	*next;
}	t_hit;

typedef struct s_param
{
	double	t;
	t_shape	*object;
	t_vec3	point;
	t_sight	sight;
	int		inside_bool;
	t_vec3	over_point;
}	t_param;

t_sphere sphere_create(t_vec3 point, double radius);
t_plane plane_create(t_vec3 pt, t_vec3 norm);
t_cylinder cylinder_create(t_vec3 pt, t_vec3 norm, double rad, double height);
t_discriminant	ray_sphere_intersect(t_ray ray, t_sphere *sphere);
// int	ray_shape_intersection(t_hit **hit_list, t_shape *shape, t_ray ray);
int	ray_shape_intersection(t_hit **hit_list, t_shape *shape, t_ray ray);
t_hit	*hit_new_intersection(double t, t_shape *shape);
void	hit_add_to_list(t_hit **hit_list, t_hit *new_hit);
void	hit_lst_print(t_hit *hit_list);
t_vec3	sphere_normal(t_shape shape, t_vec3 world_pt); // TO DELETE
t_vec3	get_normal_at(t_shape shape, t_vec3 world_pt);
t_vec3	shape_reflect(t_vec3 in, t_vec3 normal);
#endif