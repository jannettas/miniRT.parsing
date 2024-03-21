/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:57:49 by thibault          #+#    #+#             */
/*   Updated: 2023/05/03 17:47:58 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc_lib.h"
#include "inc_struct.h"
#include "inc_functions.h"
#include "inc_keycode.h"

int	handle_input(int keysym, t_data *data)
{
	if (keysym == KEY_ESCAPE)
	{
		free_table(data);
		free_all_points(data->head_list_pt);
		free_memory(data);
		exit (0);
	}
	return (0);
}

int	close_window(t_data *data)
{
	free_table(data);
	free_all_points(data->head_list_pt);
	free_memory(data);
	exit (0);
}

int	key_events(int keysym, t_data *data)
{
	key_rotation_x(keysym, data);
	key_rotation_y(keysym, data);
	key_translation(keysym, data);
	key_view_iso(keysym, data);
	key_view_ortho(keysym, data);
	key_zoom(keysym, data);
	key_z_rot(keysym, data);
	key_z_hom(keysym, data);
	return (0);
}
