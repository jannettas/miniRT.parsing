/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:21:59 by thibault          #+#    #+#             */
/*   Updated: 2024/03/21 16:55:48 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	img_pix_put(t_canevas *cnv, int x, int y, int color)
{
	char	*pixel;
	int		len;
	static int		i = 0;

	
	// if(y > 220 && x > 450)
	// 		exit(0);

	len = cnv->line_len;
	pixel = 0;
	if (x < 0 || x >= cnv->win_width || y < 0 || y >= cnv->win_height)
		return ;
	pixel = cnv->addr + (y * len + x * (cnv->bpp / 8));
	*(unsigned int *)pixel = color;
	printf("\rFor %d pixel x=%d, y=%d\n", i++, x, y);
}

void	hex_to_rgb(int hexColor, int rgb[3])
{
	rgb[0] = (hexColor >> 16) & 0xFF;	// Rouge
	rgb[1] = (hexColor >> 8) & 0xFF;	// Vert
	rgb[2] = hexColor & 0xFF;			// Bleu
}

// int	rgb_to_hex(int r, int g, int b)
// {
// 	return ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF);
// }

// int rgb_to_hex(t_color color)
// {
// 	int	red;
// 	int	green;
// 	int	blue;

// 	red = (int)color.red * 255;
// 	green = (int)color.green * 255;
// 	blue = (int)color.blue *255;

// 	return ((red) << 16) + ((green) << 8) + (blue);
// }

static int	convert(float color)
{
	if (color > 1)
		color = 1;
	color *= 255 + 0.5;
	return (color);
}

int	rgb_to_hex(t_color color)
{
	return (
		convert(color.red) << 16
		| convert(color.green) << 8
		| convert(color.blue)
	);
}

int	render_xy_pts(t_canevas *cnv, t_scn *scn)
{
	int px;
	int py;
	t_color color;
	t_ray	ray;
	t_cam	camera;

	//TEST for matrix operations
		// mx_tester(cnv);
	
	/*METHODE
		For each ray (camera->screen(x, y)), calculate if there is intersections with a shape.
		=> each ray owns its intersections list
		=> each ray end (is projected) on the caneva (aka screen), as a pixel

		Create every "intersection list (t parameter, intersected shape)" for every ray.
	*/ 
	// printf("\n cnv->win_height %d\n",cnv->win_height);
	camera = scn->camera;
	//STEP 1: For each pixel
	py = 0;
	while (py < cnv->win_height - 1)
	//TEST
	// while (py < 2)
	{
		// printf("\rRendering line %d / %d (%.1f %%)", py, cnv->win_height, ((double)py / cnv->win_height) * 100);
		px = 0;
		while (px < cnv->win_width - 1)
		//TEST
		// while (px < 3)
		{
			// STEP 1: For each pixel, calculate the ray coming from the camera and its intersection list
			// ray = ray_for_pixel(cnv- >scene->camera, px, py);
			
			//TEST
			// px = 5;
			// py = 5;


			ray = ray_for_pixel(&camera, px, py);
			

			// STEP 2: calculate the color of the pixel by finding the shape's color interceptedd by the ray
			color = get_pixel_color(scn->world, ray);
			
			//DEBUG
			if (1)
			{	
				// printf("\n== DEBUG MODE in render_xy_pts ==\n");
				// printf("For pixel px=%d, py=%d\n", px, py);
				// printf("\rFor pixel px=%d, py=%d\n", px, py);
				// if(py > 3 && px > 700)
				// 	exit(0);
				// if(py > cnv->a_r / px + 1)
					// color = color_new(1, 0, 0);
				// ray_print(ray);
				// printf("Pixel's color:\n");
				color_print(color);
				// if (color.blue == 0 && color.green == 0 && color.red == 0)
				// 	exit(0);
			}
			// STEP 3: print the color of the pixel
			img_pix_put(cnv, px, py, rgb_to_hex(color));

			px++;
		}
		py++;
	}
	printf("Rendering last pixel py %d / px%d\n", py, px);
	printf("\rRendering line %d / %d (100.0 %%)\n", cnv->win_height, cnv->win_height);
	
	
	// DEBUG
	if (0)
	{
		printf("\n== DEBUG MODE in render_xy_pts ==\n");
		printf("shape position: ");
		vec3_print(cnv->scene->world.shape_tab[0].sphere.origin);
		shape_print_material(cnv->scene->world.shape_tab[0].material);
		printf("light position: ");
		vec3_print(cnv->scene->world.light_tab[0].position);
		printf(" light intensity: ");
		color_print(cnv->scene->world.light_tab[0].intensity);
		printf("cam position: ");
		vec3_print(cnv->scene->camera.location);
		printf("cam direction: ");
		vec3_print(cnv->scene->camera.direction);
		printf("hit list: ");
		hit_lst_print(cnv->scene->world.hit_list);
	}
	//DEBUG END
	
	return (0);
}

t_ray	ray_for_pixel(t_cam	*cam, int px, int py)
{
	double	world_x;
	double	world_y;
	t_vec3	pixel;
	t_ray	ray;
	t_vec3	origin;
	t_vec3	direction;
	
	world_x = cam->lense_half_width_ratio - (px + 0.5) * cam->pixel_size;
	world_y = cam->lense_half_height_ratio - (py + 0.5) * cam->pixel_size;
	pixel = mx_vec3_multiply(cam->inverse, vec3_create(world_x, world_y, -1, 1));
	
	//TEST
	// pixel = mx_vec3_multiply(cam->inverse, vec3_create(0, 0, -1, 1));
	
	origin = mx_vec3_multiply(cam->inverse, vec3_create(0, 0, 0, 1));
	direction = vec3_normalize(vec3_substr(pixel, origin));
	ray = ray_create(origin, direction);

	//DEBUG
	if (0)
	{
		printf("\n== DEBUG MODE in ray_for_pixel ==\n");
		printf("world_x: %.2f\n", world_x);
		printf("world_y: %.2f\n", world_y);
		printf("pixel:\n");
		vec3_print(pixel);
		printf("origin:\n");
		vec3_print(origin);
		printf("direction:\n");
		vec3_print(direction);
		printf("ray:\n");
		ray_print(ray);
	}

	return (ray);
}


void	hit_sort_by_t(t_hit **hit_list)
{
	t_hit	*sorted;
	t_hit	*current;
	t_hit	*next;
	t_hit	*tmp;

	if (!hit_list || !*hit_list)
		return ;
	sorted = NULL;
	current = *hit_list;
	while (current != NULL)
	{
		next = current->next;
		current->next = NULL;
		if (sorted == NULL || current->t < sorted->t)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			tmp = sorted;
			while (tmp->next != NULL && tmp->next->t < current->t)
				tmp = tmp->next;
			current->next = tmp->next;
			tmp->next = current;
		}
		current = next;
	}
	*hit_list = sorted;
}



t_color	get_pixel_color(t_world world, t_ray ray)
{
	t_color	color;
	t_hit	*hit;
	t_param	hit_param;


	//TEST
		// ray = ray_create(vec3_create(0, 0, -5, 1), vec3_create(0, 0, 0, 0));
		// printf("\n== DEBUG MODE in get_pixel_color ==\n");
		// ray_print(ray);

	//STEP 1: find all ray/shape intersections and make a hit list
	ray_intersection(&world, ray);
	
	//STEP 2: sort hit_list in ascending order
	// hit_sort_by_t(&(world.hit_list));
	
	// if (world.hit_list->t > 0)
	// 	hit_lst_print(world.hit_list);
	// STEP 3: get first hit (it will be displayed)
	
	
	// VARIANTE 1
	hit = hit_get_closer_hit(world.hit_list); //pas necessaire, liste deja triée

	// VARIANTE 2
	// if(cnv->scene->world.hit_list)
	// 	hit = cnv->scene->world.hit_list->next;
	// else
	// 	hit = NULL;


	// printf("hit_lst_print::\n");
	// hit_lst_print(cnv->scene->world.hit_list);
	if (hit == NULL)
		return(color_new(0, 0, 0));
	// STEP 4: Get hit parameters (aka pre-computed values) for every hits ( = "prepare_computation" in the book)
	// printf("salut\n");

	//DEBUG
	// hit_lst_print(cnv->scene->world.hit_list);
	// t_hit *tmp = cnv->scene->world.hit_list->next;
	// while (tmp )
	// {
	// 	printf("hit.t %.2f\n", tmp->t);
	// 	hit_param = hit_get_param(tmp, ray);
	// 	color = color_get_hit_color(cnv->scene->world, hit_param);
		
	// 	tmp = tmp->next;
	// }
	//END DEBUG

	hit_param = hit_get_param(hit, ray);
	

	if (0 && hit_param.object->sphere.radius == 1.1)
	{
		printf("\n== DEBUG MODE in get_pixel_color ==\n");
		printf("t: ");
		printf("%.2f \n", hit_param.t);
		printf("ray: ");
		ray_print(ray);
		printf("hit_param \n");
		printf(".point: ");
		vec3_print(hit_param.point);
		printf(".sight.normalv: ");
		vec3_print(hit_param.sight.normalv);
		printf(".sight.eyev: ");
		vec3_print(hit_param.sight.eyev);
		printf("prod. of normalv and eyev: ");
		printf("%.2f \n",vec3_prod(hit_param.sight.normalv, hit_param.sight.eyev));
		printf(".inside_bool: ");
		printf("%d \n", hit_param.inside_bool);
	}
	//TEST 1
		// point = (t_vec3){0, 0, 0, 1};
		// sight.normalv = (t_vec3){0, 0, -1, 0};
		// sight.eyev = (t_vec3){0, 0, -1, 0};

	//TEST 2
		// point = (t_vec3){0, 0, 0, 1};
		// sight.normalv = (t_vec3){0, 0, -1, 0};
		// sight.eyev = (t_vec3){0, sqrt(2) / 2, -sqrt(2) / 2, 0};

	//TEST 3
		// point = (t_vec3){0, 0, 0, 1};
		// sight.normalv = (t_vec3){0, 0, -1, 0};
		// sight.eyev = (t_vec3){0, 0, -1, 0};
	
	//TEST 4
		// point = (t_vec3){0, 0, 0, 1};
		// sight.normalv = (t_vec3){0, 0, -1, 0};
		// sight.eyev = (t_vec3){0, -sqrt(2) / 2, -sqrt(2) / 2, 0};
	
	//TEST 4
		// point = (t_vec3){0, 0, 0, 1};
		// sight.normalv = (t_vec3){0, 0, -1, 0};
		// sight.eyev = (t_vec3){0, 0, -1, 0};
	
	// printf("param point:\n");
	// vec3_print(hit_param.point);

	color = color_get_hit_color(world, hit_param);
	
	//DEBUG
	// color_print(color);
	
	return (color);
}

t_param	hit_get_param(t_hit *hit, t_ray ray)
{
	t_param	hit_param;

	//prepare some pre-computed value for each hits
	
	hit_param.t = hit->t;
	hit_param.object = hit->object;
	hit_param.point = ray_get_point(ray, hit->t);
	hit_param.sight.eyev = vec3_neg(ray.direction);
	hit_param.sight.normalv = sphere_normal(*(hit->object), hit_param.point);
	hit_param.inside_bool = FALSE;
	if (vec3_prod(hit_param.sight.normalv, hit_param.sight.eyev) < 0)
	{
		hit_param.inside_bool = TRUE;
		hit_param.sight.normalv = vec3_neg(hit_param.sight.normalv);
	}
	// hit_param.over_point = vec3_add(hit_param.point, vec3_mult(hit_param.sight.normalv, EPSILON));

	// DEBUG
	// if (1 && hit_param.object->sphere.radius == 0.8)
	// {
	// 	printf("\n== DEBUG MODE in hit_get_param ==\n");
	// 	printf("t: ");
	// 	printf("%.2f \n", hit_param.t);
	// 	printf("ray: ");
	// 	ray_print(ray);
	// 	printf("hit_param \n");
	// 	printf(".point: ");
	// 	vec3_print(hit_param.point);
	// 	printf(".sight.normalv: ");
	// 	vec3_print(hit_param.sight.normalv);
	// 	printf(".sight.eyev: ");
	// 	vec3_print(hit_param.sight.eyev);
	// 	printf("prod. of normalv and eyev: ");
	// 	printf("%.2f \n",vec3_prod(hit_param.sight.normalv, hit_param.sight.eyev));
	// 	printf(".inside_bool: ");
	// 	printf("%d \n", hit_param.inside_bool);
	// }
	return (hit_param);
}



/*
PSEUDO CODE:

cnvvas <- cnvvas(cnvvas_pixels, cnvvas_pixels)
color <- color(1, 0, 0) # red
shape <- sphere
# for each row of pixels in the cnvvas
for y <- 0 to cnvvas_pixels - 1

	# compute the world y coordinate (top = + half, bottom = - half)
	world_y <- half - pixel_size * y

	# for each pixel in the row
	for x <- 0 to cnvvas pixels - 1
		# compute the world × coordinate (left = -half, right = half)
		world_x <-half + pixel_size * x

		# describe the point on the wall that the ray will target
		position <- point(world _x, world_y, wall_z)
		r <- ray(ray_origin, normalize(position - ray_origin))
		xs <- intersect(shape, r)

		if hit(xs) is defined
			write_pixel(cnvvas, x, y, color)
		end if
	end for
end for
*/

int	render(t_canevas *cnv, t_scn *scene)
{
	// void	*img;

	
	// (void)scene;
	
	// img = cnv->img_ptr;
	
	// if (cnv->win_ptr == NULL)
	// 	return (1);
	render_xy_pts(cnv, scene);
	
	//DEBUG
	if (cnv->debug_mode)
	{
		printf("\n== DEBUG MODE in render ==\n");
		printf("cnv: %p\n", cnv);
		printf("cnv->win_ptr: %p\n", cnv->win_ptr);
		printf("cnv->mlx_ptr: %p\n", cnv->mlx_ptr);
		printf("cnv: %p\n", cnv);
		printf("cnv->mlx_img: %p\n", cnv->img_ptr);
		printf("cnv->addr: %p\n", cnv->addr);
	}
	//DEBUG END 
	// mlx_put_image_to_window(cnv->mlx_ptr, cnv->win_ptr, img, 0, 0);
	
	return (0);
}

