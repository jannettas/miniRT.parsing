/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:31:25 by thibault          #+#    #+#             */
/*   Updated: 2024/03/21 15:51:56 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_STRUCT_H
# define MLX_STRUCT_H

typedef struct s_scn t_scn;
typedef struct s_world t_world;

//faire un make re si on ajoute une variable !!
// typedef struct s_img
// {
// 	void	*mlx_img;
// 	char	*addr;
// 	int		bpp;
// 	int		line_len;
// 	int		endian;
// }	t_img;

/* A canvas is a rectangular grid of pixels */
typedef struct s_canevas
{
	int		debug_mode;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	
	int		win_width;
	int		win_height;
	double	a_r;
	t_scn	*scene;
	// t_img	*img;
	
	
	
	
}	t_canevas;
#endif