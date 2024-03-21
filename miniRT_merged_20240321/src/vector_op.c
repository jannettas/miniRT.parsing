/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:50:10 by thibault          #+#    #+#             */
/*   Updated: 2024/01/03 16:16:48 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



t_vec3	vec3_create(double x, double y, double z, double w)
{
	t_vec3	v_new;

	v_new.x = x;
	v_new.y = y;
	v_new.z = z;
	v_new.w = w;
	return (v_new);
}

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v_sum;

	v_sum.x = v1.x + v2.x;
	v_sum.y = v1.y + v2.y;
	v_sum.z = v1.z + v2.z;
	return (v_sum);
}

t_vec3	vec3_substr(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v_dif;

	v_dif.x = v1.x - v2.x;
	v_dif.y = v1.y - v2.y;
	v_dif.z = v1.z - v2.z;
	return (v_dif);
}

t_vec3	vec3_neg(t_vec3 v1)
{
	t_vec3	v_neg;

	v_neg.x = - v1.x;
	v_neg.y = - v1.y;
	v_neg.z = - v1.z;
	return (v_neg);
}

t_vec3	vec3_mult(t_vec3 v1, double scalar)
{
	t_vec3	v_prod;

	v_prod.x = v1.x * scalar;
	v_prod.y = v1.y * scalar;
	v_prod.z = v1.z * scalar;
	return (v_prod);
}

t_vec3	vec3_divid(t_vec3 v1, double scalar)
{
	t_vec3	v_quot;

	v_quot.x = v1.x / scalar;
	v_quot.y = v1.y / scalar;
	v_quot.z = v1.z / scalar;
	return (v_quot);
}

double	vec3_magnitude(t_vec3 v1)
{
	double	magn;

	magn = pow(v1.x, 2) + pow(v1.y, 2) + pow(v1.z, 2);
	magn = sqrt(magn);
	return (magn);
}

t_vec3	vec3_normalize(t_vec3 v1)
{
	t_vec3 v_norm;
	double magn = vec3_magnitude(v1);

	if (magn == 0)
		return (t_vec3){0, 0, 0, 0};

	v_norm.x = v1.x / magn;
	v_norm.y = v1.y / magn;
	v_norm.z = v1.z / magn;
	return (v_norm);
}

double	vec3_prod(t_vec3 v1, t_vec3 v2)
{
	double	prod;

	prod = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (prod);
}

t_vec3	vec3_vect_prod(t_vec3 v1, t_vec3 v2)
{
	t_vec3 v_vect_prod;

	v_vect_prod.x = v1.y * v2.z - v1.z * v2.y;
	v_vect_prod.y = v1.z * v2.x - v1.x * v2.z;
	v_vect_prod.z = v1.x * v2.y - v1.y * v2.x;
	return v_vect_prod;
}

void	vec3_print(t_vec3 vector)
{
	printf("vec3: (%.2f, %.2f, %.2f | %.2f)\n", vector.x, vector.y, vector.z, vector.w);
}