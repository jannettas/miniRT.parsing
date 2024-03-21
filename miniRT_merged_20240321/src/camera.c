/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:21:59 by thibault          #+#    #+#             */
/*   Updated: 2024/03/21 21:24:25 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	mx_view_transform(t_vec3 from, t_vec3 to, t_vec3 up)
{
	t_vec3		left;
	t_vec3		upn;
	t_vec3		true_up;
	t_vec3		forward;
	double		orientation_tab[MAX_DIM][MAX_DIM];
	t_matrix	orientation;
	
	forward = vec3_normalize(vec3_substr(to, from));
	upn = vec3_normalize(up);
	left = vec3_vect_prod(forward, upn);
	true_up = vec3_vect_prod(left, forward);
	ft_bzero(orientation_tab, sizeof(double) * SIZE_MATRIX);
	orientation_tab[0][0] = left.x;
	orientation_tab[0][1] = left.y;
	orientation_tab[0][2] = left.z;
	orientation_tab[1][0] = true_up.x;
	orientation_tab[1][1] = true_up.y;
	orientation_tab[1][2] = true_up.z;
	orientation_tab[2][0] = -1 * forward.x;
	orientation_tab[2][1] = -1 * forward.y;
	orientation_tab[2][2] = -1 * forward.z;
	orientation_tab[3][0] = 0;
	orientation_tab[3][1] = 0;
	orientation_tab[3][2] = 0;
	orientation_tab[3][3] = 1;
	orientation = mx_create(orientation_tab, MAX_DIM);
	mx_create(orientation_tab, MAX_DIM);
	return (mx_mx_multiply(orientation, mx_translation(from.x, from.y, from.z)));
}
t_cam	init_camera(t_canevas *cnv, char **scene_values)
{
	t_cam	cam;
	t_vec3	location_pt;
	t_vec3	direction_pt;
	//int		fov_angle_degre;
	char 	**coord;
	char 	**norm;

	// STEP 1: PARSE parameters from input file
	// location_pt = vec3_create(0, 2, 12, 1);
	// direction_pt = vec3_create(0, 0, 0, 1);
	// fov_angle_degre = 90;
	coord = ft_split(scene_values[1], ',');
	norm = ft_split(scene_values[2], ',');
	location_pt = vec3_create(ft_atod(coord[0]), ft_atod(coord[1]),
								ft_atod(coord[2]), 1);
	//location_pt = vec3_create(0, 0, 12, 1);
	direction_pt = vec3_create(ft_atod(norm[0]), ft_atod(norm[1]),
								ft_atod(norm[2]), 1);
	//direction_pt = vec3_create(0, 0, 0, 1);
	//fov_angle_degre = ft_atoi(scene_values[3]);
	//fov_angle_degre = 90;

	//This coordinates works
	// location_pt = vec3_create(0, 1.5, -5, 1);
	// direction_pt = vec3_create(0, 0, 0, 1);
	// fov_angle_degre = 90;

	//STEP 2: Create CAMERA
	//(void)line;
	// cam = (t_cam *)malloc(sizeof(t_cam));
	// if (!(cam))
	// 	return (0);

	//STEP 3: Compute et define camera parameters
	cam.location = location_pt;
	cam.direction = direction_pt;
	cam.fov_angle_rad = degreesToRadians(ft_atoi(scene_values[3]));
	cam.a_r = cnv->a_r;
	cam.win_width = cnv->win_width;
	cam_find_pixel_size(&cam);
	
	//TEST
	// cam.transform = mx_identity_matrix();
	// cam.transform = mx_mx_multiply(mx_y_rotation(3.14/4), mx_translation(0, -2, 5));
	
	cam.transform = mx_view_transform(location_pt, direction_pt, vec3_create(0, 1, 0, 1));
	cam.inverse = mx_inverse(cam.transform);


	// Chercher les vecteurs (direction et longueur) horizontaux et verticaux qui définissent "l'écran de projection"
	// cam_find_screen_vector(cnv, cam);
	
	if (1)
	{
		printf("\n== DEBUG MODE in init_camera ==\n");
		printf("cnv->a_r: %.2f\n", cnv->a_r);
		printf("cnv->win_width: %d\n", cnv->win_width);

		// printf("cam.win_width: %.2f, cnv: %.2f \n", cam.a_r, cnv->a_r);
		// printf("cam.win_width: %.2d\n", cam.win_width);
		// printf("cam.fov_angle_rad: %.2f\n", cam.fov_angle_rad);
		// printf("cam.lense_half_width_ratio: %.2f\n", cam.lense_half_width_ratio);
		// printf("cam.lense_half_height_ratio: %.2f\n", cam.lense_half_height_ratio);
		// printf("cam.pixel_size: %f\n", cam.pixel_size);
		
		printf("cam: %p\n", &cam);
		printf("cam.coord:");
		vec3_print(cam.location);
		printf("cam.pixel_size: %.6f \n", cam.pixel_size);
		printf("cam.transform:\n");
		mx_print(cam.transform);
		printf("cam.inverse:\n");
		mx_print(cam.inverse);
	}
	return(cam);
}

// t_cam	init_camera(t_canevas *cnv, char *line)
// {
// 	t_cam	cam;
// 	t_vec3	location_pt;
// 	t_vec3	direction_pt;
// 	int		fov_angle_degre;

// 	// STEP 1: PARSE parameters from input file
// 	// location_pt = vec3_create(0, 2, 12, 1);
// 	// direction_pt = vec3_create(0, 0, 0, 1);
// 	// fov_angle_degre = 90;

// 	location_pt = vec3_create(0, 0, -12, 1);
// 	direction_pt = vec3_create(0, 0, 0, 1);
// 	fov_angle_degre = 90;

// 	//This coordinates works
// 	// location_pt = vec3_create(0, 1.5, -5, 1);
// 	// direction_pt = vec3_create(0, 0, 0, 1);
// 	// fov_angle_degre = 90;

// 	//STEP 2: Create CAMERA
// 	(void)line;
// 	// cam = (t_cam *)malloc(sizeof(t_cam));
// 	// if (!(cam))
// 	// 	return (0);

// 	//STEP 3: Compute et define camera parameters
// 	cam.location = location_pt;
// 	cam.direction = direction_pt;
// 	cam.fov_angle_rad = degreesToRadians(fov_angle_degre);
// 	cam.a_r = cnv->a_r;
// 	cam.win_width = cnv->win_width;
// 	cam_find_pixel_size(&cam);
	
// 	//TEST
// 	// cam.transform = mx_identity_matrix();
// 	// cam.transform = mx_mx_multiply(mx_y_rotation(3.14/4), mx_translation(0, -2, 5));
	
// 	cam.transform = mx_view_transform(location_pt, direction_pt, vec3_create(0, -1, 0, 1));
// 	cam.inverse = mx_inverse(cam.transform);


// 	// Chercher les vecteurs (direction et longueur) horizontaux et verticaux qui définissent "l'écran de projection"
// 	// cam_find_screen_vector(cnv, cam);
	
// 	if (1)
// 	{
// 		printf("\n== DEBUG MODE in init_camera ==\n");
// 		printf("cnv->a_r: %.2f\n", cnv->a_r);
// 		printf("cnv->win_width: %d\n", cnv->win_width);

// 		// printf("cam.win_width: %.2f, cnv: %.2f \n", cam.a_r, cnv->a_r);
// 		// printf("cam.win_width: %.2d\n", cam.win_width);
// 		// printf("cam.fov_angle_rad: %.2f\n", cam.fov_angle_rad);
// 		// printf("cam.lense_half_width_ratio: %.2f\n", cam.lense_half_width_ratio);
// 		// printf("cam.lense_half_height_ratio: %.2f\n", cam.lense_half_height_ratio);
// 		// printf("cam.pixel_size: %f\n", cam.pixel_size);
		
// 		printf("cam: %p\n", &cam);
// 		printf("cam.coord:");
// 		vec3_print(cam.location);
// 		printf("cam.pixel_size: %.6f \n", cam.pixel_size);
// 		printf("cam.transform:\n");
// 		mx_print(cam.transform);
// 		printf("cam.inverse:\n");
// 		mx_print(cam.inverse);
// 	}
// 	return(cam);
// }

double degreesToRadians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

void	cam_find_pixel_size(t_cam *cam)
{

	double	half_view_ratio;
	double	d_focal;

	d_focal = 1;
	half_view_ratio = tanf(cam->fov_angle_rad / 2) / d_focal;
	if (cam->a_r >= 1)
	{
		cam->lense_half_width_ratio= half_view_ratio;
		cam->lense_half_height_ratio = half_view_ratio / cam->a_r;
	}
	else
	{
		cam->lense_half_width_ratio = half_view_ratio *  cam->a_r;
		cam->lense_half_height_ratio = half_view_ratio;
	}
	// pixel_size est calculé en divisant la largeur totale du plan de projection par la résolution horizontale de l'image (nombre de pixels horizontaux)
	cam->pixel_size = (cam->lense_half_width_ratio * 2) / cam->win_width;
	
	//DEBUG
		printf("\n== DEBUG MODE in cam_find_pixel_size ==\n");
		printf("cam.win_width: %.2d\n", cam->win_width);
		printf("cam.fov_angle_rad: %.2f\n", cam->fov_angle_rad);
		printf("half_view_ratio: %.2f\n", half_view_ratio);
		printf("cam.lense_half_width_ratio: %.2f\n", cam->lense_half_width_ratio);
		printf("cam.lense_half_height_ratio: %.2f\n", cam->lense_half_height_ratio);
		printf("cam.pixel_size: %f\n", cam->pixel_size);
	
}
