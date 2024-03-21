/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:02:42 by thibault          #+#    #+#             */
/*   Updated: 2024/03/07 16:09:40 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef WORLD_H
# define WORLD_H

typedef struct s_hit t_hit;
typedef struct s_color t_color;
typedef struct s_light t_light;
typedef struct s_shape t_shape;
typedef struct s_light t_light;

typedef struct s_world
{
	t_hit	*hit_list; //equ. to `xs`
	t_color	color;
	int		nb_shape;
	t_shape	*shape_tab;
	int		nb_light;
	t_light	*light_tab;
	// t_light	light;
}	t_world;

#endif