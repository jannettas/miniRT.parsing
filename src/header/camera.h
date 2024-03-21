/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:31:25 by thibault          #+#    #+#             */
/*   Updated: 2024/03/21 16:07:44 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

typedef struct s_cam
{
	char	ID;
	t_vec3	location;
	t_vec3	direction;
	double	fov_angle_degre;
	double	fov_angle_rad;
	
	// cnv param
	int		win_width;

	//lense_param
	double	lense_width_ratio;
	double	lense_height_ratio;
	double	lense_half_width_ratio;
	double	lense_half_height_ratio;
	double	a_r;
	double	pixel_size;

	//cam matrix
	t_matrix	transform;	
	t_matrix	inverse;	
}	t_cam;


t_cam	init_camera(t_canevas *cnv, char **scene_values);
void	cam_find_pixel_size(t_cam *cam);
double	degreesToRadians(double degrees);


#endif