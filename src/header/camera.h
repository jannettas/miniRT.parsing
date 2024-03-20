/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:31:25 by thibault          #+#    #+#             */
/*   Updated: 2024/03/15 16:55:09 by thibault         ###   ########.fr       */
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


t_cam	init_camera(t_canevas *cnv, char *line);
void	cam_find_pixel_size(t_cam *cam);
double	degreesToRadians(double degrees);


#endif