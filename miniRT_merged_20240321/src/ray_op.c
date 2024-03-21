/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:50:10 by thibault          #+#    #+#             */
/*   Updated: 2024/03/14 09:17:01 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_create(t_vec3 point, t_vec3 vector)
{
	t_ray	new_ray;

	new_ray.origin = point;
	new_ray.direction = vector;
	return (new_ray);
}

t_vec3 ray_get_point(t_ray ray, double t)
{
	t_vec3	destination_pt;

	if (0)
	{
		printf("\n== DEBUG MODE in ray_get_point ==\n");
		printf("ray:\n");
		ray_print(ray);
		printf("ray.origin:\n");
		vec3_print(ray.origin);
		printf("ray.direction:\n");
		vec3_print(ray.direction);
		printf("ray.t:%.2f\n", t);
	}
	
	destination_pt = vec3_add(ray.origin, vec3_mult(ray.direction, t));
	return (destination_pt);
}

t_ray	ray_transform(t_ray r, t_matrix m)
{
	t_ray	transformed_ray;

	transformed_ray = ray_create(
		mx_vec3_multiply(m, r.origin),
		mx_vec3_multiply(m, r.direction));
	return (transformed_ray);
}

void	ray_print(t_ray ray)
{
	printf("ray: o(%.2f, %.2f, %.2f | %.2f) d(%.2f, %.2f, %.2f | ", 
	ray.origin.x,
	ray.origin.y,
	ray.origin.z,
	ray.origin.w,
	ray.direction.x,
	ray.direction.y,
	ray.direction.z);
	if (ray.direction.w > 1)
		printf("> 1)\n");
	else if (ray.direction.w == 1)
		printf("1)\n");
	else if (ray.direction.w == 0)
		printf("0)\n");
	else
		printf("<= 0)\n");
}