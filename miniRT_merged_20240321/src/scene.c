/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:21:59 by thibault          #+#    #+#             */
/*   Updated: 2024/03/23 14:27:25 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_scene(char *scene_file, t_canevas *cnv, t_scn *scene)
{
	// t_scn	*scene;
	// t_canevas	*cnv;
	//char		*line;
	//int			count;

	//(void)scene_file;
	
	//init cnv
	
	//init scene
	// scene = (t_scn *)malloc(sizeof(t_scn));
	// if (!(scene))
	// 	return (0);
	cnv->scene = scene;
	//scene->camera = init_camera(cnv, scene_file); // will be initialized in parse_line
	count_shapes_lights(scene_file, scene);
	scene->world.light_tab = create_light_tab(scene->world.nb_light);
	scene->world.shape_tab = create_shape_tab(scene->world.nb_shape);
	parse_scene(scene_file, cnv, scene);
	if (1)
	{
		printf("\n== DEBUG MODE in init_scene ==\n");
		printf("cnv->a_r: %.2f\n", cnv->a_r);
		printf("cnv->win_width: %d\n", cnv->win_width);
		printf("cam: %p\n", &scene->camera);
		printf("cam.coord:");
		vec3_print(scene->camera.location);
		printf("cam.pixel_size: %.6f \n", scene->camera.pixel_size);
		printf("cam.transform:\n");
		// mx_print(scene->camera.transform);
		printf("cam.inverse:\n");
		mx_print(scene->camera.inverse);
	}
	
	/*
		// PSEUDO-CODE !!!

		//STEP 0: open file

		fd_file = open(scene_file);

		// STEP 1: parse input_file 1x to get nb_shape and nb lights (OR create a function to expand shape_tab when needed)

		nb_shape = parse_input_file(fd_file);
		scene->world.shape_tab = create_shape_tab(nb_shape);
		
		//STEP 2: parse file, line by line, and create scene = camera + world. World = shapes + lights.

		line = get_next_line(fd_file);
		while (line)
		{
			if (line[0] == 'C')
				scene->camera = init_camera(line);
			if (line[0] == 'L')
				scene->light = init_light(line);
			if (line[0] == 'S')
				add_sphere(scene, line);
			if (line[0] == 'P')
				add_plane(scene, line);
			if (line[0] == 'C')
				add_cylindre(scene, line);
			line = get_next_line(scene file);
		}	
	*/

	// TEMPORARY CODE: create 4 spheres

		// line = NULL;
		// scene->world.nb_shape = 5;
		// scene->world.shape_tab = create_shape_tab(scene->world.nb_shape);
		// count = 0;
		// add_shape_sphere(&(scene->world.shape_tab[count]), line);
		// count = 1;
		// add_shape_sphere_N(&(scene->world.shape_tab[count]), line);
		// count = 2;
		// add_shape_sphere_S(&(scene->world.shape_tab[count]), line);
		// count = 3;
		// add_shape_sphere_E(&(scene->world.shape_tab[count]), line);
		// count = 4;
		// add_shape_sphere_W(&(scene->world.shape_tab[count]), line);
		
		int i = 0;
		while (i < scene->world.nb_shape)
		{
			// t_shape *tmp_shape = &scene->world.shape_tab[i];
			printf("shape nb: %d, pt: %p", i, &scene->world.shape_tab[i]);
			// if (tmp_shape->type_of_shape == SPHERE)
			// 	printf("radius : %.2f\n", tmp_shape->sphere.radius);
			i++;
		}
	// TEMPORARY CODE: create light
		// scene->world.nb_light = 2;
		// scene->world.light_tab = create_light_tab(scene->world.nb_light);
		// count = 0;
		// add_light(&(scene->world.light_tab[count]), line);
		// count = 1;
		// add_light_2(&(scene->world.light_tab[count]), line);
		// light = add_light(line);
	

	// DEBUG
	if (cnv->debug_mode)
	{
		printf("\n== DEBUG MODE in init_scene ==\n");
		printf("cnv->scene: %p\n", cnv->scene);
	}

	return (0);
}

t_shape	*create_shape_tab(int nb_shape)
{
	t_shape	*shape_tab;
	
	shape_tab = (t_shape *)malloc(nb_shape * sizeof(t_shape));
	if (!(shape_tab))
		return (0);
	return (shape_tab);
}

t_light	*create_light_tab(int nb_light)
{
	t_light	*light_tab;
	
	light_tab = (t_light *)malloc(nb_light * sizeof(t_light));
	if (!(light_tab))
		return (0);
	return (light_tab);
}

/*
	TYPICAL VALUES
	ambient = 0 to 1
	diffuse = 0 to 1
	specular = 0 to 1
	shininess = 10 to 200
*/

t_material	shape_init_material(t_color color)
{
	t_material	m;

	m.color = color;
	m.ambient = color_multiply((t_color){1, 1, 1}, world.ambiant.ratio);
	m.ambient = (t_color){0.1, 0.1, 0.1};
	// m.ambient = &world.ambiant
	m.diffuse = 0.7;
	m.specular = 0.3;
	m.shininess = 200;
	return (m);
}

void	shape_print_material(t_material m)
{
	printf("\nPRINT Material: \n");
	printf("color: ");
	color_print(m.color);
	printf("m.ambient: ");
	color_print(m.ambient);
	printf("diffuse: %.2f \n", m.diffuse);
	printf("specular: %.2f \n", m.specular);
	printf("shininess: %.2f \n", m.shininess);
}

// THIS FCT IS TO TEST and should be deleted at the end
// void	add_shape_sphere_N(t_shape *shape_elem, char *line)
// {	
// 	t_vec3		o_sphere;
// 	double		radius;
// 	t_color		color;
// 	t_matrix	scale;
// 	t_matrix	transform;
// 	t_matrix	inverse;
// 	t_matrix	transpose;

// 	(void)line;
// 	if (!shape_elem)
// 		return;

// 	o_sphere = vec3_create(0, 2, 0, 1);
// 	// o_sphere = vec3_create(-1.5, 0.33, -0.75, 1);
// 	radius = 1.1;

// 	shape_elem->sphere = sphere_create(o_sphere, radius);
// 	shape_elem->type_of_shape = SPHERE;
// 	color = (t_color){0, 0, 1};
// 	shape_elem->material = shape_init_material(color);
// 	transform = mx_translation(o_sphere.x, o_sphere.y, o_sphere.z);
// 	scale = mx_scaling(radius, radius, radius);
// 	transform = mx_mx_multiply(transform, scale);
// 	inverse = mx_inverse(transform);
// 	transpose = mx_transpose(inverse);
// 	shape_elem->transform = transform;
// 	shape_elem->inverse = inverse;
// 	shape_elem->transpose = transpose;
// }

// void	add_shape_sphere_S(t_shape *shape_elem, char *line)
// {	
// 	t_vec3		o_sphere;
// 	double		radius;
// 	t_color		color;
// 	t_matrix	scale;
// 	t_matrix	transform;
// 	t_matrix	inverse;
// 	t_matrix	transpose;

// 	(void)line;
// 	if (!shape_elem)
// 		return;

// 	o_sphere = vec3_create(0, -2, 0, 1);
// 	radius = 0.9;

// 	shape_elem->sphere = sphere_create(o_sphere, radius);
// 	shape_elem->type_of_shape = SPHERE;
// 	color = (t_color){1, 0, 0};
// 	shape_elem->material = shape_init_material(color);
// 	transform = mx_translation(o_sphere.x, o_sphere.y, o_sphere.z);
// 	scale = mx_scaling(radius, radius, radius);
// 	transform = mx_mx_multiply(transform, scale);
// 	inverse = mx_inverse(transform);
// 	transpose = mx_transpose(inverse);
// 	shape_elem->transform = transform;
// 	shape_elem->inverse = inverse;
// 	shape_elem->transpose = transpose;
// }

// void	add_shape_sphere_E(t_shape *shape_elem, char *line)
// {	
// 	t_vec3		o_sphere;
// 	double		radius;
// 	t_color		color;
// 	t_matrix	scale;
// 	t_matrix	transform;
// 	t_matrix	inverse;
// 	t_matrix	transpose;

// 	(void)line;
// 	if (!shape_elem)
// 		return;

// 	o_sphere = vec3_create(2, 0, 0, 1);
// 	radius = 1.2;

// 	shape_elem->sphere = sphere_create(o_sphere, radius);
// 	shape_elem->type_of_shape = SPHERE;
// 	color = (t_color){1, 1, 0};
// 	shape_elem->material = shape_init_material(color);
// 	transform = mx_translation(o_sphere.x, o_sphere.y, o_sphere.z);
// 	scale = mx_scaling(radius, radius, radius);
// 	transform = mx_mx_multiply(transform, scale);
// 	inverse = mx_inverse(transform);
// 	printf("add_shape_sphere_E:: inverse\n");
// 	mx_print(inverse);

// 	transpose = mx_transpose(inverse);
// 	shape_elem->transform = transform;
// 	shape_elem->inverse = inverse;
// 	shape_elem->transpose = transpose;
// }

// void	add_shape_sphere_W(t_shape *shape_elem, char *line)
// {	
// 	t_vec3		o_sphere;
// 	double		radius;
// 	t_color		color;
// 	t_matrix	scale;
// 	t_matrix	transform;
// 	t_matrix	inverse;
// 	t_matrix	transpose;

// 	(void)line;
// 	if (!shape_elem)
// 		return;

// 	o_sphere = vec3_create(-2, 0, 0, 1);
// 	radius = 0.8;

// 	shape_elem->sphere = sphere_create(o_sphere, radius);
// 	shape_elem->type_of_shape = SPHERE;
// 	color = (t_color){0, 1, 0};
// 	shape_elem->material = shape_init_material(color);
// 	transform = mx_translation(o_sphere.x, o_sphere.y, o_sphere.z);
// 	scale = mx_scaling(radius, radius, radius);
// 	transform = mx_mx_multiply(transform, scale);
// 	inverse = mx_inverse(transform);
// 	transpose = mx_transpose(inverse);
// 	shape_elem->transform = transform;
// 	shape_elem->inverse = inverse;
// 	shape_elem->transpose = transpose;
// }


// void	add_shape_sphere(t_shape *shape_elem, char **scene_values)
// {	
// 	char		**coord;
// 	char		**col;
// 	t_vec3		o_sphere;
// 	double		radius;
// 	t_color		color;
// 	// probably will make a separate function for matrix transformations
// 	t_matrix	scale;
// 	t_matrix	transform;
// 	t_matrix	inverse;
// 	t_matrix	transpose;

// 	//STEP 1: Nothing. check if shape_elem is existing
// 	if (!shape_elem)
// 		return;
// 	coord = ft_split(scene_values[1], ',');
// 	col = ft_split(scene_values[3], ',');
// 	if (count_tokens(scene_values) != 4
// 		|| count_tokens(coord) != 3	|| count_tokens(col) != 3)
// 	{
// 		perror("Correct format: sp [origin x,y,z] [radius] [color R,G,B]\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	//STEP 2: parse and get SPHERE attribute (origin, radius).
// 	shape_elem->sphere.origin = (vec3_create)(ft_atod(coord[0]),
// 								ft_atod(coord[1]), ft_atod(coord[2]), 1);
// 	shape_elem->sphere.radius = ft_atod(scene_values[2]) / 2;
// 	//note: here we set manually the attributes
// 	// o_sphere = vec3_create(-0.5, 1, 0.5, 1);
// 	//o_sphere = vec3_create(0, 0, 0, 1);
// 	//radius = 1;
// 	//shape_elem->sphere = sphere_create(o_sphere, radius);
// 	shape_elem->sphere = sphere_create(shape_elem->sphere.origin,
// 										shape_elem->sphere.radius);
// 	shape_elem->type_of_shape = SPHERE;
// 	//STEP 3: parse and get SHAPE attribute (color).
// 	color = (t_color){ft_atod(col[0]), ft_atod(col[1]), ft_atod(col[2])};
// 	//color = (t_color){1, 0, 1};
// 	shape_elem->material = shape_init_material(color);
// 	free_split(coord);
//     free_split(col);
// 	//STEP 3: calculate SHAPE matrix - in a separate function?
// 	o_sphere = shape_elem->sphere.origin;
// 	radius = shape_elem->sphere.radius;
// 	// radius /= 2; //diviser le rayon par deux ?
// 	transform = mx_translation(o_sphere.x, o_sphere.y, o_sphere.z);
// 	scale = mx_scaling(radius, radius, radius);
// 	transform = mx_mx_multiply(transform, scale);
// 	inverse = mx_inverse(transform);
// 	transpose = mx_transpose(inverse);
	
// 	shape_elem->transform = transform;
// 	shape_elem->inverse = inverse;
// 	shape_elem->transpose = transpose;
	
// 	//TESTS
// 		// shape_elem->transform = mx_mx_multiply(shape_elem->transform, mx_scaling(0.5, 0.5, 0.5));
// 		// shape_elem->transform = mx_mx_multiply(shape_elem->transform, mx_translation(5, 0, 0));
// 		// shape_elem->transform = mx_mx_multiply(shape_elem->transform, mx_shearing((t_shearing){0.1, 0}, (t_shearing){0.1, 0}, (t_shearing){0, 0}));
// 		// shape_elem->material.ambient = (t_color){1, 1, 1};
		
// 	//TEST
// 		// shape_print_material(shape_elem->material);
	
// 	//TEST 1
// 		// normal = sphere_normal(*shape_elem, (t_vec3){sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3, 1});
// 		// printf("vecteur normal:\n");
// 		// vec3_print(normal);

// 	//TEST 2
// 		// reflect = shape_reflect((t_vec3){1, -1, 0, 1}, (t_vec3){0, 1, 0, 1});
// 		// reflect = shape_reflect((t_vec3){0, -1, 0, 1}, (t_vec3){sqrt(2) / 2, sqrt(2) / 2, 0, 1});
// 		// printf("vecteur reflect:\n");
// 		// vec3_print(reflect);

// 		if (0)
// 		{
// 			printf("\n== DEBUG MODE in add_shape_sphere ==\n");
// 			printf("mx transform\n");
// 			mx_print(shape_elem->transform);
// 			printf("mx scale\n");
// 			mx_print(scale);
// 			printf("mx inverse\n");
// 			mx_print(shape_elem->inverse);
// 			printf("mx transpose\n");
// 			mx_print(shape_elem->transpose);
// 		}
// }

/*
	TYPICAL VALUES
	ambient = 0 to 1
	diffuse = 0 to 1
	specular = 0 to 1
	shininess = 10 to 200
*/
