/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:23:31 by zsoltani          #+#    #+#             */
/*   Updated: 2024/03/23 14:27:19 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
// ∗ identifier: pl
// ∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
// ∗ 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 
// 0.0,1.0,0.0
// ∗ R,G,B colors in range [0-255]: 0,0,225

void	add_shape_plane(t_shape *shape_elem, char **scene_values)
{
	char		**coord;
	char		**norm;
	char		**col;

	//STEP 1: Nothing. check if shape_elem is existing
	if (!shape_elem)
		return;
	coord = ft_split(scene_values[1], ',');
	norm = ft_split(scene_values[2], ',');
	col = ft_split(scene_values[3], ',');
	if (check_plane(scene_values, coord, norm, col) == 0)
		return;
	//STEP 2: parse and get PLANE attribute (origin, normal).
	shape_elem->plane.origin = (vec3_create)(ft_atod(coord[0]),
						ft_atod(coord[1]), ft_atod(coord[2]), 1);
	shape_elem->plane.normal = (vec3_create)(ft_atod(norm[0]),
								ft_atod(norm[1]), ft_atod(norm[2]), 0);
	shape_elem->plane = plane_create(shape_elem->plane.origin, 
									shape_elem->plane.normal);
	shape_elem->type_of_shape = PLANE;
	//STEP 3: parse and get SHAPE attribute (color).
	shape_elem->material = shape_init_material((t_color){ft_atod(col[0]),
										ft_atod(col[1]), ft_atod(col[2])});
	free_split(coord);
	free_split(norm);
	free_split(col);
}

// ∗ identifier: cy
// ∗ x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
// ∗ 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis:
// 0.0,0.0,1.0
// ∗ the cylinder diameter: 14.2
// ∗ the cylinder height: 21.42
// ∗ R,G,B colors in range [0,255]: 10, 0, 255

void	add_shape_cylinder(t_shape *shape_elem, char **scene_values, t_world *world)
{
	char		**coord;
	char		**norm;
	char		**col;
	t_vec3		point;
	t_vec3		normal;

	//STEP 1: check if shape_elem is existing
	if (!shape_elem)
		return;
	coord = ft_split(scene_values[1], ',');
	norm = ft_split(scene_values[2], ',');
	col = ft_split(scene_values[5], ',');
	if (check_cylinder(scene_values, coord, norm, col) == 0)
		return;
	//STEP 2: parse and get CYLINDRE attribute (point, normal, radius, height).
	point = (vec3_create)(ft_atod(coord[0]), ft_atod(coord[1]), 
							ft_atod(coord[2]), 1);
	normal = (vec3_create)(ft_atod(norm[0]), ft_atod(norm[1]),
							ft_atod(norm[2]), 0);
	shape_elem->cylinder.radius = ft_atod(scene_values[3]) / 2;
	shape_elem->cylinder.height = ft_atod(scene_values[4]);
	shape_elem->cylinder = cylinder_create(point, normal,
					shape_elem->cylinder.radius, shape_elem->cylinder.height);
	shape_elem->type_of_shape = CYLINDRE;
	//STEP 3: parse and get SHAPE attribute (color).
	shape_elem->material = shape_init_material((t_color){ft_atod(col[0]),
											ft_atod(col[1]), ft_atod(col[2])});
	shape_elem.material.ambient = world->ambient;
	free_split(coord);
	free_split(norm);
	free_split(col);
	//STEP 4: calculate SHAPE matrix - in a separate function?

}

void	add_shape_sphere(t_shape *shape_elem, char **scene_values)
{	
	char		**coord;
	char		**col;
	t_vec3		o_sphere;
	double		radius;
	t_color		color;
	// probably will make a separate function for matrix transformations
	t_matrix	scale;
	t_matrix	transform;
	t_matrix	inverse;
	t_matrix	transpose;

	//STEP 1: Nothing. check if shape_elem is existing
	if (!shape_elem)
		return;
	coord = ft_split(scene_values[1], ',');
	// printf("coord: %s\n", coord[0]);
	col = ft_split(scene_values[3], ',');
	if (check_sphere(scene_values, coord, col) == 0)
		return;
	//STEP 2: parse and get SPHERE attribute (origin, radius).
	shape_elem->sphere.origin = vec3_create(ft_atod(coord[0]), 
									ft_atod(coord[1]), ft_atod(coord[2]), 1);

	vec3_print(shape_elem->sphere.origin);
	shape_elem->sphere.radius = ft_atod(scene_values[2]) / 2;
	shape_elem->sphere = sphere_create(shape_elem->sphere.origin, 
									shape_elem->sphere.radius);
	shape_elem->type_of_shape = SPHERE;
	
	//STEP 3: parse and get SHAPE attribute (color).
	color = (t_color){ft_atod(col[0]), ft_atod(col[1]), ft_atod(col[2])};
	//color = (t_color){1, 0, 1};
	shape_elem->material = shape_init_material(color);
	free_split(coord);
    free_split(col);
	//STEP 3: calculate SHAPE matrix - in a separate function?
	o_sphere = shape_elem->sphere.origin;
	radius = shape_elem->sphere.radius;
	// radius /= 2; //diviser le rayon par deux ?
	transform = mx_translation(o_sphere.x, o_sphere.y, o_sphere.z);
	scale = mx_scaling(radius, radius, radius);
	transform = mx_mx_multiply(transform, scale);
	inverse = mx_inverse(transform);
	transpose = mx_transpose(inverse);
	
	shape_elem->transform = transform;
	shape_elem->inverse = inverse;
	shape_elem->transpose = transpose;

	printf("radius: %.2f\n", shape_elem->sphere.radius);
	
	//TESTS
		// shape_elem->transform = mx_mx_multiply(shape_elem->transform, mx_scaling(0.5, 0.5, 0.5));
		// shape_elem->transform = mx_mx_multiply(shape_elem->transform, mx_translation(5, 0, 0));
		// shape_elem->transform = mx_mx_multiply(shape_elem->transform, mx_shearing((t_shearing){0.1, 0}, (t_shearing){0.1, 0}, (t_shearing){0, 0}));
		// shape_elem->material.ambient = (t_color){1, 1, 1};
		
	//TEST
		// shape_print_material(shape_elem->material);
	
	//TEST 1
		// normal = sphere_normal(*shape_elem, (t_vec3){sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3, 1});
		// printf("vecteur normal:\n");
		// vec3_print(normal);

	//TEST 2
		// reflect = shape_reflect((t_vec3){1, -1, 0, 1}, (t_vec3){0, 1, 0, 1});
		// reflect = shape_reflect((t_vec3){0, -1, 0, 1}, (t_vec3){sqrt(2) / 2, sqrt(2) / 2, 0, 1});
		// printf("vecteur reflect:\n");
		// vec3_print(reflect);

		if (0)
		{
			printf("\n== DEBUG MODE in add_shape_sphere ==\n");
			printf("mx transform\n");
			mx_print(shape_elem->transform);
			printf("mx scale\n");
			mx_print(scale);
			printf("mx inverse\n");
			mx_print(shape_elem->inverse);
			printf("mx transpose\n");
			mx_print(shape_elem->transpose);
		}
}
