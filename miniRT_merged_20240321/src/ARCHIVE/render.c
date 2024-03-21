/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:21:59 by thibault          #+#    #+#             */
/*   Updated: 2024/03/21 15:51:47 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "fdf.h"
#include "inc_lib.h"
#include "inc_struct.h"
#include "inc_functions.h"

void	img_pix_put(t_data *data, int x, int y, int color)
{
	char	*pixel;
	char	*addr;
	int		len;

	addr = data->addr;
	len = data->line_len;
	pixel = 0;
	if (x >= 0 && x < data->winx && y >= 0 && y < data->winy)
	{
		pixel = addr + (y * len + x * (data->bpp / 8));
		*(unsigned int *)pixel = color;
	}	
}

void	render_background(t_data *data, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->winx)
	{
		j = 0;
		while (j < data->winx)
		{
			img_pix_put(data, j++, i, color);
		}
		++i;
	}
}

int	render_xy_pts(t_data *data, t_pt *head_list_pt)
{
	t_pt	*tmp;

	if (!head_list_pt)
		return (0);
	tmp = head_list_pt;
	while (tmp != 0)
	{
		img_pix_put(data, *(tmp->x), *(tmp->y), *(tmp->color));
		tmp = tmp->next;
	}
	return (0);
}

int	render_mesh(t_data *data)
{
	t_pt	***tabp;
	int		col;
	int		li;

	tabp = data->table_of_points;
	col = 0;
	li = 0;
	while (li < data->nb_y)
	{
		col = 0;
		while (col < data->nb_x)
		{
			render_segment(data, tabp[li][col], tabp[li][col + 1]);
			render_segment(data, tabp[li][col], tabp[li + 1][col]);
			if (col + 1 == data->nb_x)
				render_segment(data, tabp[li][col + 1], tabp[li + 1][col + 1]);
			if (li + 1 == data->nb_y)
				render_segment(data, tabp[li + 1][col], tabp[li + 1][col + 1]);
			col++;
		}
		li++;
	}
	return (0);
}

int	render(t_data *data)
{
	void	*img;

	img = data->mlx_img;
	if (data->win_ptr == NULL)
		return (1);
	render_background(data, 0x000000);
	render_xy_pts(data, data->head_list_pt);
	render_mesh(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, 0, 0);
	render_txt(data);
	return (0);
}

/*
int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}
*/