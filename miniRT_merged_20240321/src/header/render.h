/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:29:09 by thibault          #+#    #+#             */
/*   Updated: 2024/03/20 15:53:26 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

/*render.c*/
int		render(t_canevas *cnv, t_scn *scn);
void	img_pix_put(t_canevas *cnv, int x, int y, int color);
void	hex_to_rgb(int hexColor, int rgb[3]);
// int		rgb_to_hex(int r, int g, int b);
int		rgb_to_hex(t_color color);
int		render_xy_pts(t_canevas *cnv, t_scn *scn);
t_ray	ray_for_pixel(t_cam	*cam, int px, int py);
t_color		get_pixel_color(t_world world, t_ray ray);
t_param	hit_get_param(t_hit *hit, t_ray ray);

#endif
