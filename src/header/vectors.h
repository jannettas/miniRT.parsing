/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:29:09 by thibault          #+#    #+#             */
/*   Updated: 2024/01/03 18:46:51 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_vec3;

/*vector_op.c*/
t_vec3	vec3_create(double x, double y, double z, double w);
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_substr(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_neg(t_vec3 v1);
t_vec3	vec3_mult(t_vec3 v1, double scalar);
t_vec3	vec3_divid(t_vec3 v1, double scalar);
double	vec3_magnitude(t_vec3 v1);
t_vec3	vec3_normalize(t_vec3 v1);
double	vec3_prod(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_vect_prod(t_vec3 v1, t_vec3 v2);
void	vec3_print(t_vec3 vector);

#endif
