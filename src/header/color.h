/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:31:25 by thibault          #+#    #+#             */
/*   Updated: 2024/01/03 20:18:16 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
	double	red;
	double	green;
	double	blue;
}	t_color;

/* color.c */
t_color	color_new(double red, double green, double blue);
t_color	color_add(t_color a, t_color b);
t_color	color_subtract(t_color a, t_color b);
t_color	color_multiply(t_color color, double scalar);
t_color	color_hadamard_product(t_color a, t_color b);
void	color_print(t_color color);
#endif