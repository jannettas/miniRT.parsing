/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:17:28 by thibault          #+#    #+#             */
/*   Updated: 2023/05/10 16:50:28 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc_lib.h"
#include "inc_struct.h"
#include "inc_functions.h"

int	handle_map(char *mapname, t_data *data)
{
	t_pt	*tmp;

	tmp = new_pt(0, 0, 0, 0);
	read_map(mapname, tmp);
	data->head_list_pt = tmp->next;
	free(tmp->x);
	free(tmp->y);
	free(tmp->z);
	free(tmp->color);
	free(tmp);
	tmp = NULL;
	xyz_minmax(data);
	init_table_of_points(data);
	free_all_yxz_minmax(data);
	pts_to_table(data);
	set_xyz_init(data);
	return (0);
}

int	init_mlx(t_data *d)
{
	t_img	*i;

	d->img = (t_img *)malloc(sizeof(t_img));
	if (!d->img)
		free(d->img);
	i = d->img;
	d->mlx_ptr = mlx_init();
	if (d->mlx_ptr == NULL)
		free(d->mlx_ptr);
	d->winx = 1280;
	d->winy = 960;
	d->win_ptr = mlx_new_window(d->mlx_ptr, d->winx, d->winy, "FdF");
	if (d->win_ptr == NULL)
		return (1);
	i->mlx_img = mlx_new_image(d->mlx_ptr, d->winx, d->winy);
	if (i->mlx_img == NULL)
		free(i->mlx_img);
	i->addr = mlx_get_data_addr(i->mlx_img, &i->bpp, &i->line_len, &i->endian);
	if (i->addr == NULL)
		free(i->addr);
	return (0);
}

int	init_geom(t_data *data)
{
	init_param_rot(data);
	init_param_translation(data);
	init_param_homoth(data);
	pts_rotation(data, 45, 45, 0);
	pts_rot_sumop(data, 45, 45, 0);
	xyz_fit_to_win(data, 1);
	return (0);
}

int	handle_events(t_data *data)
{
	mlx_key_hook(data->win_ptr, &handle_input, data);
	mlx_hook(data->win_ptr, 2, 0, &key_events, data);
	mlx_hook(data->win_ptr, 17, 0, &close_window, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}

int	main(int argc, char **map_name)
{
	t_data	*data;

	if (argc == 2)
		ft_putstr_fd(map_name[1], 1);
	else
	{
		ft_putstr_fd("une SEULE map à la fois, pas plus, pas moins...\n", 1);
		exit (0);
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (0);
	handle_map(map_name[1], data);
	init_mlx(data);
	init_geom(data);
	render(data);
	handle_events(data);
	return (0);
}
