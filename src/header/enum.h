/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:56:14 by thibault          #+#    #+#             */
/*   Updated: 2024/03/11 14:58:40 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum e_check
{
	OK,
	ERROR
}	t_e_check;

typedef enum e_caract_matrix
{
	MAX_DIM = 4,
	SIZE_MATRIX = 16
}	t_e_caract_matrix;

typedef enum e_shape
{
	SPHERE = 1,
	PLANE = 2,
	CYLINDRE = 3
}	t_e_shape;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_e_bool;
#endif
