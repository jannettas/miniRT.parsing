/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:21:59 by thibault          #+#    #+#             */
/*   Updated: 2024/03/13 14:57:06 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_new(double red, double green, double blue)
{
	return ((t_color)
	{
		red, green, blue,
	});
}

t_color	color_add(t_color a, t_color b)
{
	return ((t_color)
	{
		a.red + b.red,
		a.green + b.green,
		a.blue + b.blue
	});
}

t_color	color_subtract(t_color a, t_color b)
{
	return ((t_color)
	{
		a.red - b.red,
		a.green - b.green,
		a.blue - b.blue
	});
}

t_color	color_multiply(t_color color, double scalar)
{
	return ((t_color)
	{
		color.red * scalar,
		color.green * scalar,
		color.blue * scalar,
	});
}

t_color	color_hadamard_product(t_color a, t_color b)
{
	return ((t_color)
	{
		a.red * b.red,
		a.green * b.green,
		a.blue * b.blue
	});
}

void	color_print(t_color color)
{
	printf("color RGB: (%.4f, %.4f, %.4f)\n", color.red, color.green, color.blue);
}