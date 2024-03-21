/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:50:10 by thibault          #+#    #+#             */
/*   Updated: 2024/03/20 11:34:29 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define HIT_MAX	256

t_hit	*hit_new_intersection(double t, t_shape *shape)
{
	
	static t_hit	hits_tab[HIT_MAX]; //
	static	int		hit_index; //The variables hits_tab and hit_index are static in order to keep the value in memory  between every function's calls
	static t_hit	*new_hit;

	
	new_hit = hits_tab + (hit_index++ % HIT_MAX); //the module is needed to avoid memory access outside the table
	new_hit->object = shape;
	new_hit->t = t;
	new_hit->next = NULL;

	//DEBUG
		// printf("\n== DEBUG MODE in  ==\n");
		// printf("new_hit: %p\n", new_hit);
		// printf("t: %.2f\n", t);
		// printf("rayon: %.2f\n", new_hit->object->sphere.radius);
	
	return (new_hit);
}


t_hit	*hit_get_last(t_hit *hit)
{
	if (!hit)
		return (0);
	while (hit->next != 0)
		hit = hit->next;
	return (hit);
}

// VARIANTE 1
// void	hit_add_to_list(t_hit **hit_list, t_hit *new_hit)
// {
// 	t_hit	*last_hit;

// 	last_hit = hit_get_last(*hit_list);
// 	if (last_hit == 0)
// 		*hit_list = new_hit;
// 	else
// 		last_hit->next = new_hit;
// }

// VARIANTE 2
void	hit_add_to_list(t_hit **hit_list, t_hit *new_hit)
{
	t_hit	*prev;
	t_hit	*curr;

	prev = NULL;
	curr = *hit_list;
	while (curr && curr->t < new_hit->t)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev == NULL)
	{
		new_hit->next = *hit_list;
		*hit_list = new_hit;
		return ;
	}
	prev->next = new_hit;
	new_hit->next = curr;
}

t_hit	*ray_intersection(t_world *world, t_ray ray)
{
	// t_hit	*ray_hit_list;
	int		shape_index;
	t_shape	*shape;
	
	
	
	world->hit_list = NULL;
	shape = world->shape_tab;
	shape_index = 0;
	// printf("nb_shapes %d\n", world->nb_shape);
	while(shape_index < world->nb_shape)
	{
		
		shape = world->shape_tab + shape_index;
		// printf("ray_intersection:: shape pt: %p shape nb: %d, , shape pt: %p shape radius= %.2f\n", shape, shape_index, shape, shape->sphere.radius);
		ray_shape_intersection(&world->hit_list, shape, ray);
		
		// if(ray.hit_list->next && ray.hit_list->next->object->sphere.radius == 0.9)
		// {	
		// 	printf("ray_intersection:: INTERSECTION sphere's radius: %.2f\n", ray.hit_list->object->sphere.radius);
		// 	printf("ray_intersection:: t: %.2f\n", ray.hit_list->t);
		// 	// exit(0);
		// }

		// hit_lst_print(world->hit_list);
		shape_index++;
	}

	//DEBUG
	// if (cnv->debug_mode)
	// {
	// 	printf("\n== DEBUG MODE in ray_intersection ==\n");
	// 	printf("cnv: %p\n", cnv);
	// 	printf("cnv->scene: %p\n", cnv->scene);
	// 	printf("cnv->scene->world.hit_list: %p\n", cnv->scene->world.hit_list);
	// 	printf("ray_hit_list: %p\n", ray_hit_list);

	// }
	//DEBUG END 
	return (world->hit_list);
}

/*
 * Function: ft_isnan
 * -------------------
 * Checks if a given floating-point number is NaN (Not a Number).
 * Utilizes the property that NaN is the only floating-point value
 * that is not equal to itself. If the comparison x != x is true,
 * the value is considered NaN, and the function returns 1. 
 * Otherwise, it returns 0, indicating the value is not NaN.
 *
 * Parameters:
 *   x - The floating-point number to check.
 *
 * Returns:
 *   1 if x is NaN, 0 otherwise.
 */


int ft_isnan(double x)
{	
	return (x != x);
}

int	ray_shape_intersection(t_hit **hit_list, t_shape *shape, t_ray ray)
{
	t_discriminant	discr;
	t_ray			local_ray;
	int				intersect;
	
	intersect = FALSE;

	// printf("shape pt: %p\n", shape);
	// printf("ray\n");
	// ray_print(ray);
	// printf("shape->inverse\n");
	// mx_print(shape->inverse);


	local_ray = ray_transform(ray, shape->inverse);

		

	// if(shape->type_of_shape == SPHERE)
	// {
		
		discr = ray_sphere_intersect(local_ray, &shape->sphere);
		// if(discr.discr > 0 && shape->sphere.radius == 0.9)
		// {	
		// 	printf("ray_shape_intersection:: INTERSECTION sphere's radius: %.2f\n", shape->sphere.radius);
		// 	printf("ray_shape_intersection:: new_det.discr: %.2f\n", discr.discr);
		// 	// exit(0);
		// }


		// VARIANTE 1
		// if(discr.discr < 0)
		// {
		// 	intersect = FALSE;
		// 	return (intersect);
		// }
		
		// printf("shape's rayon: %.2f\n", shape->sphere.radius);

		// hit_add_to_list(hit_list, hit_new_intersection(discr.t1, shape));
		// hit_add_to_list(hit_list, hit_new_intersection(discr.t2, shape));
		
		//DEBUG
		// if ( discr.t1 > 0 |  discr.t2 > 0)
		// {
		// 	printf("hit t1 = %.2f\n", discr.t1);
		// 	printf("hit t2 = %.2f\n", discr.t2);
		// }
		
		//VARIANTE 2
		if (discr.discr >= 0 && !ft_isnan(discr.t1))
		{
			hit_add_to_list(hit_list, hit_new_intersection(discr.t1, shape));
			intersect = 1;
		}
		if (discr.discr >= 0 && !ft_isnan(discr.t2))
		{
			hit_add_to_list(hit_list, hit_new_intersection(discr.t2, shape));
			intersect = 1;
		}
	// }
	
 

	//DEBUG
		// if (discr.t1 || discr.t2)
		// {
		// // if (shape->sphere.radius != 1)
		// 	{
		// 		printf("\n== DEBUG MODE in ray_shape_intersection ==\n");
		// 		printf("-- Sphere intersected points --\n");
		// 		printf("sphere r = %.2f origin:", shape->sphere.radius);
		// 		vec3_print(shape->sphere.origin);

		// 		ray_print(ray);
		// 		ray_print(local_ray);
		// 		printf("mx transform\n");
		// 		mx_print(shape->transform);
		// 		printf("mx inverse (transform)\n");
		// 		mx_print(shape->inverse);
		// 		printf("discr = %.2f\n", discr.discr);
		// 		printf("hit t1 = %.2f\n", discr.t1);
		// 		vec3_print(ray_get_point(ray, discr.t1));
		// 		printf("hit t2 = %.2f\n", discr.t2);
		// 		vec3_print(ray_get_point(ray, discr.t2));
		// 	}
		// }

	intersect = TRUE;
	return (intersect);
}

// VARIANTE 1
t_hit	*hit_get_closer_hit(t_hit *hit_list)
{
	t_hit	*tmp;
	t_hit	*hit;
	double	t;

	if (hit_list == NULL)
		return (0);
	// printf("t: %.2f\n", hit_list->t);
	tmp = hit_list;
	t = tmp->t;
	hit = tmp;
	while (tmp)
	{
		if (tmp->next && tmp->next->t)
		{
			if ((tmp->next->t < t && tmp->next->t >= 0)|| tmp->t <= 0.0001) // we don't take negative value
			{	
				t = tmp->next->t;
				hit = tmp->next;

			}
		}
		tmp = tmp->next;
	}
	//TEST
	// if (hit->object->sphere.radius == 0.8)
	// 	printf("hit t:%.2f, radius %.2f\n", hit->t, hit->object->sphere.radius);
	// 	printf("hit on a sphere NOT at the center\n");
	
	return (hit);
}

// VARIANTE 2
// t_hit	*hit_get_closer_hit(t_hit *hit_list)
// {
// 	// if (hit_list)
// 	// 	hit_lst_print(hit_list);
// 	while (hit_list != NULL && hit_list->t <= 0.0001)
// 		hit_list = hit_list->next;
// 	return (hit_list);
// }

// VARIANTE 2b
// t_hit	*hit_get_closer_hit(t_hit *hit_list)
// {
// 	while (hit_list != NULL && hit_list->t <= 0.0001)
// 		hit_list = hit_list->next;
// 	return (hit_list);
// }

void	hit_lst_print(t_hit *hit_list)
{
	t_hit	*tmp;
	int		i;

	
	tmp = hit_list;
	if (tmp == NULL)
	{
		printf("-->hit list empty\n");
		return ;
	}
	printf("\n--  hits --\n");
	i = 0;
	while (tmp)
	{
		// if(tmp->object->type_of_shape == SPHERE && tmp->object->sphere.radius == 1.2)
		// {
			printf("sphere's radius : %.2f\n", tmp->object->sphere.radius);
			printf("--> hit n° %d, t = %.2f\n", i, tmp->t);
		// }
		i++;
		tmp = tmp->next;
	}
	printf("==> Total hits: %d \n", i);
}