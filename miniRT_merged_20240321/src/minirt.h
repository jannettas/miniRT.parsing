/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:13:42 by thibault          #+#    #+#             */
/*   Updated: 2024/03/21 21:34:14 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/*System's headers*/
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>

/*Minishell header files*/
# include "./lib/libft/libft.h"
# include "./lib/minilibx/mlx.h"
# include "./header/enum.h"
# include "./header/vectors.h"
# include "./header/matrix.h"
# include "./header/camera.h"
# include "./header/ray.h"
# include "./header/color.h"
# include "./header/material.h"
# include "./header/light.h"
# include "./header/shapes.h"
# include "./header/parser.h"



# include "./header/world.h"
# include "./header/scene.h"
# include "./header/mlx_struct.h"





# include "./header/render.h"
# include "./header/inc_keycode.h"


/* miniRT.c */
int		init_cnv(t_canevas *cnv);
int		free_and_exit(t_canevas *mlx_cnv);
int		close_window(t_canevas *mlx_cnv);
int		handle_events(t_canevas *mlx_cnv);

#endif