/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@stucnvent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Createcnv: 2023/08/06 15:14:08 by thibault          #+#    #+#             */
/*   Upcnvatecnv: 2023/12/13 16:26:11 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* MLX function*/

/*
	- Parse scene
		- check error
		- init scene variables (debug mode, camera, light, volume, etc)
	- Compute
	- Init minilibx
	- Render
	- Free
*/

t_scn	clean_and_init_scene(void)
{
	t_scn		scene;

	scene.world.hit_list = NULL;
	scene.world.shape_tab = NULL;
	scene.world.nb_shape = 0;
	scene.world.light_tab = NULL;
	scene.world.nb_light = 0;
	// scene.world.color = 
	return (scene);
}

int	print_on_window(t_canevas *cnv, char *win_title)
{
	cnv->win_ptr = mlx_new_window(cnv->mlx_ptr, cnv->win_width, cnv->win_height, win_title);
	if (cnv->win_ptr == NULL)
	{
		free_and_exit(cnv);
		return (1);
	}
	return (0);
}

int	show_window(t_canevas *cnv)
{
	mlx_put_image_to_window(cnv->mlx_ptr, cnv->win_ptr, cnv->img, 0, 0);
	return (0);
}

int	main(int argc, char **scene_name)
{
	t_canevas		canevas;
	t_scn			scene;

	if (argc == 2 && (ft_check_extension(scene_name[1], ".rt", 4) == 0))
		printf("miniRT creating %s...\n", scene_name[1]);
	else
	{
		ft_putstr_fd("./miniRT [scene_name].rt\n", 1);
		exit (666);
	}
	//STEP 1: INITIALIZING THEN PARSING 
	init_cnv(&canevas);
	scene = clean_and_init_scene();
	if (parse_and_check_scene(scene_name[1], &canevas, &scene)) // if == 1, error
		free_and_exit(&canevas);
	
	//STEP 2: RENDERING
	render(&canevas, &scene);
	print_on_window(&canevas, "miniRT");
	mlx_expose_hook(canevas.win_ptr, show_window, &canevas);

	//STEP 2: EXIT AND FREE
	handle_events(&canevas);
	free_and_exit(&canevas);
	return (0);
}

int	init_cnv(t_canevas *cnv)
{
	// t_img	*i;
	// t_canevas	*cnv;

	// cnv = (t_canevas *)malloc(sizeof(t_canevas));
	// if (!(cnv))
	// 	return (0);
	cnv->debug_mode = 1;
	// cnv->img = (t_img *)malloc(sizeof(t_img));
	// if (!cnv->img)
	// 	return (NULL);
	// i = cnv->img;
	cnv->mlx_ptr = mlx_init();
	if (cnv->mlx_ptr == NULL)
		return (1);

	// cnv->win_width = 1280;
	cnv->win_width = 740;
	// cnv->win_width = 320;
	//  cnv->win_width = 11;
	cnv->a_r = 16.0 / 9.0;
	// cnv->a_r = 11.0 / 11.0;
	cnv->win_height = cnv->win_width / cnv->a_r;

	cnv->img = mlx_new_image(cnv->mlx_ptr, cnv->win_width, cnv->win_height);
	if (cnv->img == NULL)
		return (1);
	
	// i->addr = mlx_get_data_addr(i->mlx_img, &i->bpp, &i->line_len, &i->endian);
	// if (i->addr == NULL)
	// 	free(i->addr);

	cnv->img->addr = mlx_get_data_addr(cnv->img, &cnv->img->bpp,
			&cnv->img->line_len, &cnv->img->endian);
	if (!cnv->img->addr)
		return (1);



	
	// cnv->img = i;

	if (cnv->debug_mode)
	{
		printf("\n== DEBUG MODE in init_cnv ==\n");
		printf("cnv: %p\n", cnv);
		printf("cnv->win_ptr: %p\n", cnv->win_ptr);
		printf("cnv->mlx_ptr: %p\n", cnv->mlx_ptr);
		printf("cnv->img: %p\n", cnv->img);
		printf("cnv->img->mlx_img: %p\n", cnv->img->mlx_img);
		printf("cnv->img->addr: %p\n", cnv->img->addr);
		

	}
	return (0);
}

int	free_and_exit(t_canevas *cnv)
{
	// t_hit *tmp;
	// t_hit *tmp_to_free;

	mlx_destroy_window(cnv->mlx_ptr, cnv->win_ptr);
	free(cnv->mlx_ptr);  
	// free(cnv->scene->camera);
	//free(cnv->scene->world.light_tab);
	//free(cnv->scene->world.shape_tab);

	// tmp = cnv->scene->world.hit_list;
	// while (tmp)
	// {
	// 	tmp_to_free = tmp;
	// 	tmp = tmp->next;
	// 	free(tmp_to_free);
	// }

	free(cnv->img);

	
	return (0);
}

int	handle_input(int keysym, t_canevas *cnv)
{
	if (keysym == KEY_ESCAPE)
	{
		free_and_exit(cnv);
		exit (0);
	}
	return (0);
}

int	close_window(t_canevas *cnv)
{
	free_and_exit(cnv);
	exit (0);
}

int	handle_events(t_canevas *cnv)
{
	mlx_hook(cnv->win_ptr, 17, 0, &close_window, cnv);
	mlx_key_hook(cnv->win_ptr, &handle_input, cnv);
	mlx_loop(cnv->mlx_ptr);
	return (0);
}
