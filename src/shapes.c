/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:21:59 by thibault          #+#    #+#             */
/*   Updated: 2024/03/21 15:40:50 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere sphere_create(t_vec3 pt, double rad)
{
	t_sphere	new_sphere;

	new_sphere.radius = rad;
	new_sphere.origin = pt;
	return (new_sphere);
}

t_plane plane_create(t_vec3 pt, t_vec3 norm)
{
	t_plane	new_plane;

	new_plane.origin = pt;
	new_plane.normal = norm;
	return (new_plane);
}

t_cylinder cylinder_create(t_vec3 pt, t_vec3 norm, double rad, double height)
{
	t_cylinder	new_cylinder;

	new_cylinder.origin = pt;
	new_cylinder.normal = norm;
	new_cylinder.radius = rad;
	new_cylinder.height = height;
	return (new_cylinder);
}

// # the vector from the sphere's center, to the ray origin
// # remember: the sphere is centered at the world origin
// sphere_to_ray = ray.origin - point(0, 0, 0)
// a = dot(ray.direction, ray.direction)
// b = 2 * dot(ray.direction, sphere to ray)
// c = dot(sphere_to_ray, sphere_to_ray) - 1
// discriminant = b^2-4 * a * c

t_discriminant	ray_sphere_intersect(t_ray ray, t_sphere *sphere)
{
	t_vec3	sphere_to_ray;
	t_discriminant	new_det;

	
	// printf("ray_sphere_intersect:: sphere's radius: %.2f\n", sphere->radius);
	sphere_to_ray = vec3_substr(ray.origin, sphere->origin);
	new_det.a = vec3_prod(ray.direction, ray.direction);
	new_det.b = 2 * vec3_prod(ray.direction, sphere_to_ray);
	new_det.c = vec3_prod(sphere_to_ray, sphere_to_ray) - 1;
	new_det.discr = (new_det.b * new_det.b) - (4 * new_det.a * new_det.c);
	if (new_det.discr >= 0)
	{
		printf("ray_sphere_intersect:: INTERSECTION sphere's radius: %.2f\n", sphere->radius);
		new_det.t1 = (-new_det.b + sqrt(new_det.discr)) / (2 * new_det.a);
		new_det.t2 = (-new_det.b - sqrt(new_det.discr)) / (2 * new_det.a);
	}


	// printf("ray_sphere_intersect:: sphere's radius: %.2f\n", sphere->radius);
	// vec3_print(ray.origin);
	// vec3_print(sphere->origin);
	// if(new_det.discr > 0 && sphere->radius != 1)
	// {	
		printf("ray_sphere_intersect:: new_det.discr: %.2f\n", new_det.discr);
	// 	exit(0);
	// }

	return (new_det);
}

// PSEUDO-CODE
// function normal_at(sphere, world_point)
// object_point <- inverse(sphere.transform) * world_point
// object_normal <- object_point - point(0, 0, 0)
// world_normal <- transpose(inverse(sphere.transform)) * object_normal
// world_normal.w <- 0
// return normalize(world_normal)
// end function


//TO DELETE
t_vec3	sphere_normal(t_shape shape, t_vec3 world_pt)
{
	t_vec3	shape_pt;
	t_vec3	shape_normal;
	t_vec3	world_normal;
	
	shape_pt = mx_vec3_multiply(shape.inverse, world_pt);
	shape_normal = vec3_substr(shape_pt, (t_vec3){0, 0, 0, 1});
	world_normal = mx_vec3_multiply(mx_transpose(mx_inverse(shape.transform)), shape_normal);	
	world_normal.w = 0;
	world_normal = vec3_normalize(world_normal);

	// TEST
		// printf("world_pt:\n");
		// vec3_print(world_pt);
		// printf("shape_pt:\n");
		// vec3_print(shape_pt);
		// printf("shape_normal:\n");
		// vec3_print(shape_normal);
		// printf("world_normal:\n");
		// vec3_print(world_normal);	
	return (world_normal);
}


t_vec3	get_normal_at(t_shape shape, t_vec3 world_pt)
{
	t_vec3	shape_pt;
	t_vec3	shape_normal;
	t_vec3	world_normal;
	
	shape_pt = mx_vec3_multiply(shape.inverse, world_pt);
	shape_normal = (t_vec3){0, 0, 0, 1};
	if (shape.type_of_shape == SPHERE)
	{
		shape_normal = vec3_substr(shape_pt, (t_vec3){0, 0, 0, 1});
	}
	else if (shape.type_of_shape == PLANE)
	{
		//TO COMPLETE
	}
	else if (shape.type_of_shape == CYLINDRE)
	{
		//TO COMPLETE
	}
	world_normal = mx_vec3_multiply(shape.transpose, shape_normal);	
	world_normal.w = 0;
	world_normal = vec3_normalize(world_normal);

	// TEST
		// printf("world_pt:\n");
		// vec3_print(world_pt);
		// printf("shape_pt:\n");
		// vec3_print(shape_pt);
		// printf("shape_normal:\n");
		// vec3_print(shape_normal);
		// printf("world_normal:\n");
		// vec3_print(world_normal);	
	return (world_normal);
}


t_vec3	shape_reflect(t_vec3 in, t_vec3 normal)
{
	t_vec3	tmp;

	tmp = vec3_mult(normal, 2);
	tmp = vec3_mult(tmp, vec3_prod(in, normal));
	return (vec3_substr(in, tmp));
}

// PSEUDO CODE
// function reflect (in, normal)
// return in - normal * 2 * dot(in, normal)
// end function