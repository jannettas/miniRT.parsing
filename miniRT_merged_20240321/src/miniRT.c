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
		free(cnv->win_ptr);
		return (1);
	}
	return (0);
}

int	show_window(t_canevas *cnv)
{
	mlx_put_image_to_window(cnv->mlx_ptr, cnv->win_ptr, cnv->img_ptr, 0, 0);
	return (0);
}

void	img_pix_put_test(t_canevas *cnv, int x, int y, int color)
{
	char	*pixel;
	int		len;
	// static int		i = 0;

	
	// if(y > 220 && x > 450)
	// 		exit(0);
	

	len = cnv->line_len;
	pixel = 0;
	if (x < 0 || x >= cnv->win_width || y < 0 || y >= cnv->win_height)
		return ;
	pixel = cnv->addr + (y * len + x * (cnv->bpp / 8));
	*(unsigned int *)pixel = color;
	// printf("\rFor %d pixel x=%d, y=%d\n", i++, x, y);
}

int	render_test(t_canevas *cnv)
{
	int py = 0;
	while (py < cnv->win_height - 1)
	{
		int px = 0;
		while (px < cnv->win_width - 1)
		{
			t_color color = color_new(1, 0, 0);
			// printf("Pixel's color:\n");
			// color_print(color);
			// if (color.blue == 0 && color.green == 0 && color.red == 0)
			// 	exit(0);
			img_pix_put_test(cnv, px, py, rgb_to_hex(color));
			px++;
		}
		py++;
	}
	return (0);
}

int	init_cnv_test(t_canevas *cnv)
{
	
	cnv->debug_mode = 1;
	

	cnv->win_width = 120;
	printf("cnv->a_r %.2f\n", cnv->a_r);
	cnv->a_r = 2;
	printf("cnv->a_r %.5f\n", cnv->a_r);
	cnv->win_height = cnv->win_width / cnv->a_r;

	cnv->mlx_ptr = mlx_init();
	if (cnv->mlx_ptr == NULL)
		return (1);
	cnv->img_ptr = mlx_new_image(cnv->mlx_ptr, cnv->win_width, cnv->win_height);
	if (cnv->img_ptr == NULL)
		return (1);
	cnv->addr = mlx_get_data_addr(cnv->img_ptr, &cnv->bpp,
			&cnv->line_len, &cnv->endian);
	if (!cnv->addr)
		return (1);

	if (cnv->debug_mode)
	{
		printf("\n== DEBUG MODE in init_cnv_test ==\n");
		printf("cnv: %p\n", cnv);
		printf("cnv->win_ptr: %p\n", cnv->win_ptr);
		printf("cnv->mlx_ptr: %p\n", cnv->mlx_ptr);
		printf("cnv: %p\n", cnv);
		printf("cnv->mlx_img: %p\n", cnv->img_ptr);
		printf("cnv->addr: %p\n", cnv->addr);
		printf("cnv->win_height %d\n", cnv->win_height);
		printf("cnv->win_width %d\n", cnv->win_width);
		printf("cnv->a_r %.2f\n", cnv->a_r);
		

	}
	return (0);
}


// int	main(int argc, char **scene_name)
// {
// 	t_canevas		canevas;

// 	if (argc == 2)
// 		printf("miniRT creating %s...\n", scene_name[1]);
// 	else
// 	{
// 		ft_putstr_fd("./miniRT [scene_name]\n", 1);
// 		exit (666);
// 	}
// 	init_cnv_test(&canevas);
// 	render_test(&canevas);
// 	print_on_window(&canevas, "miniRT");
// 	mlx_expose_hook(canevas.win_ptr, show_window, &canevas);
// 	handle_events(&canevas);
// 	// exit(0);
// 	return (0);
// }

int	main(int argc, char **scene_name)
{
	t_canevas		canevas;
	t_scn			scene;

	if (argc == 2 && (ft_check_extension(scene_name[1], ".rt", 4) == 0))
		printf("miniRT creating %s...\n", scene_name[1]);
	else
	{
		ft_putstr_fd("./miniRT [scene_name]\n", 1);
		exit (666);
	}
	//STEP 1: INITIALIZING THEN PARSING 
	init_cnv(&canevas);
	scene = clean_and_init_scene();
	if (parse_and_check_scene(scene_name[1], &canevas, &scene))
		free_and_exit(&canevas);
	
	// //STEP 2: RENDERING
		if (1)
	{
		printf("\n== DEBUG MODE in main ==\n");
		printf("canevas->win_ptr: %p\n", canevas.win_ptr);
	}
	//printf("spher radius %.2f\n", canevas.scene->world.shape_tab[0].sphere.radius);
	render(&canevas, &scene);
	print_on_window(&canevas, "miniRT");
	mlx_expose_hook(canevas.win_ptr, show_window, &canevas);

	// FROM  GITHUB
	// mlx_hook(canvas.win_ptr, DESTROYNOTIFY, NOEVENTMASK, quit, &canvas);
	// mlx_key_hook(canvas.win_ptr, handle_keypress, &canvas);

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
	// cnv = (t_img *)malloc(sizeof(t_img));
	// if (!cnv)
	// 	return (NULL);
	// i = cnv;


	// cnv->win_width = 1280;
	cnv->win_width = 740;
	// cnv->win_width = 320;
	//  cnv->win_width = 11;
	// cnv->a_r = 16.0 / 9.0;
	cnv->a_r =2.0 / 1.0 ;
	cnv->win_height = cnv->win_width / cnv->a_r;


	cnv->mlx_ptr = mlx_init();
	if (cnv->mlx_ptr == NULL)
		return (1);


	cnv->img_ptr = mlx_new_image(cnv->mlx_ptr, cnv->win_width, cnv->win_height);
	if (cnv->img_ptr == NULL)
		return (1);
	cnv->addr = mlx_get_data_addr(cnv->img_ptr, &cnv->bpp,
			&cnv->line_len, &cnv->endian);
	if (!cnv->addr)
		return (1);

	if (cnv->debug_mode)
	{
		printf("\n== DEBUG MODE in init_cnv ==\n");
		printf("cnv: %p\n", cnv);
		printf("cnv->win_ptr: %p\n", cnv->win_ptr);
		printf("cnv->mlx_ptr: %p\n", cnv->mlx_ptr);
		printf("cnv: %p\n", cnv);
		printf("cnv->mlx_img: %p\n", cnv->img_ptr);
		printf("cnv->addr: %p\n", cnv->addr);
		

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
	free(cnv->scene->world.light_tab);
	free(cnv->scene->world.shape_tab);

	// tmp = cnv->scene->world.hit_list;
	// while (tmp)
	// {
	// 	tmp_to_free = tmp;
	// 	tmp = tmp->next;
	// 	free(tmp_to_free);
	// }

	free(cnv);

	
	return (0);
}

int	handle_input(int keysym, t_canevas *cnv)
{
	if (keysym == KEY_ESCAPE)
	{
		(void)cnv;
		// free_and_exit(cnv);
		exit (0);
	}
	return (0);
}

int	close_window(t_canevas *cnv)
{
	(void)cnv;
	// free_and_exit(cnv);
	exit (0);
}

int	handle_events(t_canevas *cnv)
{
	mlx_hook(cnv->win_ptr, 17, 0, &close_window, cnv);
	mlx_key_hook(cnv->win_ptr, &handle_input, cnv);
	mlx_loop(cnv->mlx_ptr);
	return (0);
}
