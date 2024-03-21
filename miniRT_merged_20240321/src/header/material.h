/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:31:25 by thibault          #+#    #+#             */
/*   Updated: 2024/03/07 10:33:43 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

typedef struct s_vec3 t_vec3;
typedef struct s_color t_color;

typedef struct s_material
{
	t_color		color;
	t_color		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	// t_pattern	pattern;
}	t_material;

typedef struct s_exposure
{
	t_color		effective_color;
	t_vec3		lightv;
	t_vec3		reflectv;
	float		light_dot_normal;
	float		reflect_dot_eye;
	float		factor;
}	t_exposure;
#endif

/* scene.c */
t_material	shape_init_material(t_color color);
void	shape_print_material(t_material m);