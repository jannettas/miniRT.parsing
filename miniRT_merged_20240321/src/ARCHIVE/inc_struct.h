/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:31:25 by thibault          #+#    #+#             */
/*   Updated: 2023/05/08 23:25:35 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INC_STRUCT_H
# define INC_STRUCT_H

typedef struct s_state
{
	int		x;
	int		y;
	int		z;
	int		sx;
	int		sy;
	int		sz;
	int		err1;
	int		err2;
	double	grad_z_color;
}	t_state;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_pt
{
	double		*x;
	double		*y;
	double		*z;
	int			*color;
	double		*x_init;
	double		*y_init;
	double		*z_init;
	struct s_pt	*next;
}	t_pt;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		winx;
	int		winy;
	t_img	*img;
	t_pt	*head_list_pt;
	t_pt	***table_of_points;
	int		nb_x;
	int		nb_y;
	double	*x_max;
	double	*y_max;
	double	*z_max;
	double	*x_min;
	double	*y_min;
	double	*z_min;
	double	*deg_x;
	double	*deg_y;
	double	*deg_z;
	double	*hom_x;
	double	*hom_y;
	double	*hom_z;
	int		*tr_x;
	int		*tr_y;
}	t_data;
#endif