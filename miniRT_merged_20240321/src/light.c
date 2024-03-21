/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:21:59 by thibault          #+#    #+#             */
/*   Updated: 2024/03/18 17:06:07 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//"shade_hit" function in the book
t_color	color_get_hit_color(t_world world, t_param param)
{
	t_color color;
	int		i;
	
	
	color = color_new(0, 0, 0);
	i = 0;
	// printf("world.nb_light: %d\n", world.nb_light);
	while(i < world.nb_light)
	{
		
		/*
			FROM REPO
			world.lights[index].in_shadow = is_shadowed(&world, comps.over_point, index);
		*/

		// world.light_tab[i].in_shadow = is_shadowed(&world, world.hit_list.over_point, i);
		//fonction is_shadowed to implement

		color = color_add(color, lighting(param.object, world.light_tab[i], param.point, param.sight));
		
		
		//DEBUG
		if(0 && param.object->sphere.radius < 1)
		{
			printf("\n== DEBUG MODE in color_get_hit_color ==\n");
			printf("param.object %p:\n", &param.object);
			printf("param.object %p:\n", &param.object->material.color);
			color_print(param.object->material.color);
			shape_print_material(param.object->material);
			printf("param.sight %p:\n", &param.sight);
			printf("param.t %.2f:\n", param.t);
			printf("in color_get_hit_color :: param.point:\n");
			vec3_print(param.point);
			printf("color returned: \n");
			color_print(color);
		}

		i++;
	}
	return (color);
}

	

//PSEUDO CODE
/*

function lighting(material, light, point, eyev, normalv)
# combine the surface color with the light's color/intensity
effective_color <- material.color * light.intensity
# find the direction to the light source
lightv <- normalize(light.position - point)
# compute the ambient contribution
ambient <- effective color * material.ambient
# light_dot_normal represents the cosine of the angle between the
# light vector and the normal vector. A negative number means the
# light is on the other side of the surface.
light_dot_normal <- dot(lightv, normalv)
if light_dot normal < 0
diffuse <- black
specular <- black
else
# compute the diffuse contribution
diffuse <- effective _color * material.diffuse * light_dot_normal
# reflect_dot_eye represents the cosine of the angle between the
# reflection vector and the eye vector. A negative number means the
# light reflects away from the eye.
reflectv <- reflect(-lightv, normalv)
reflect_dot_eye <- dot(reflectv, eyev)
if reflect_dot_eye <= 0
specular <- black
else
# compute the specular contribution
factor <- pow(reflect_dot_eye, material.shininess)
specular <- light.intensity * material.specular * factor
end if
end if
# Add the three contributions together to get the final shading
return ambient + diffuse + specular
end function
*/

t_color	lighting(t_shape *shape, t_light light, t_vec3 point, t_sight sight)
{
	t_exposure	e;
	t_color		color;
	

	// ORIGINAL:  
	// if (shape->material.pattern.has_pattern)
	// 	color = pattern_at_shape(shape->material.pattern, shape, point);
	// else
		// printf("shape->material %p:\n", &shape->material);
		// printf("shape->material.color: ");
		// color_print(shape->material.ambient);
	color = shape->material.color;
	//TEST
		// printf("shape color:\n");
		// color_print(color);

	// 1.combine the surface color with the light's color/intensity
	e.effective_color = color_hadamard_product(color, light.intensity);
	
	//DEBUG
		// if((0) && (light.intensity.red > 0.01|| light.intensity.blue > 0.01|| light.intensity.green > 0.01))
		// {
		// 	printf("light.intensity: ");
		// 	color_print(light.intensity);
		// }	
		// if(e.effective_color.red > 0.01|| e.effective_color.blue > 0.01|| e.effective_color.green > 0.01)
		// {
		// 	printf("e.effective_color: ");
		// 	color_print(e.effective_color);
		// }	

	// 2. find the direction to the light source
	e.lightv = vec3_normalize(vec3_substr(light.position, point));
	

	// 3. light_dot_normal represents the cosine of the angle between the
	// light vector and the normal vector.
	// A negative number means the light is on the other side of the surface.
	e.light_dot_normal = vec3_prod(e.lightv, sight.normalv);

	// 3. compute the ambient contribution
	// ORIGINAL:
	// if (e.light_dot_normal < 0 || light.in_shadow == TRUE)
	if (e.light_dot_normal < 0)
		color = dark_exposure(shape->material, e);
	else
	{
		//5. compute the diffuse contribution
		color = light_exposure(shape->material, light, e, sight);
	}

	//DEBUG
	// if(color.red > 0.01|| color.blue > 0.01|| color.green > 0.01)
	// {
		// printf("\n== DEBUG MODE in lighting ==\n");
		// printf("e.light_dot_normal: %.2f\n", e.light_dot_normal); 	
		// printf("IN\n");
		// printf("eyev: ");
		// vec3_print(sight.eyev);
		// printf("normalv: ");
		// vec3_print(sight.normalv);
		// printf("point (light): ");
		// vec3_print(point);
		// printf("color (light): ");
		// color_print(light.intensity);
		// printf("RESULT -> lighting color: ");
		// color_print(color);
	// 	if (rgb_to_hex(color))
	// 		printf("color in hex: %x\n", rgb_to_hex(color));

	// }
	return (color);
}

t_color	dark_exposure(t_material m, t_exposure e)
{
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;

	// dark_exposure -> light_dot_normal < 0 =>A negative number means the light is on the other side of the surface.
	// 4. compute the ambient contribution
	ambient = color_hadamard_product(e.effective_color, m.ambient);
	diffuse = color_new(0, 0, 0);
	specular = color_new(0, 0, 0);

	//DEBUG
	if (0)
	{
		printf("== DEBUG in DARK EXPOSURE ==\n");
		printf("m.ambient ");
		color_print(m.ambient);
		printf("e.effective_color ");
		color_print(e.effective_color);
		printf("ambient ");
		color_print(ambient);
		printf("result ");
		color_print(color_add(color_add(ambient, diffuse), specular));	
	}
	return (color_add(color_add(ambient, diffuse), specular));
}

t_color	light_exposure(t_material m, t_light light,	t_exposure e, t_sight sight)
{
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;

	// 4. compute the ambient contribution
	ambient = color_hadamard_product(e.effective_color, m.ambient);
	//5. compute the diffuse contribution
	diffuse = color_multiply(e.effective_color, m.diffuse * e.light_dot_normal);
	// reflect_dot_eye represents the cosine of the angle between the
	// reflection vector and the eye vector.
	// A negative number means the light reflects away from the eye.
	e.reflectv = shape_reflect(vec3_neg(e.lightv), sight.normalv);	
	// e.reflectv = shape_reflect(e.lightv, sight.normalv);
	//DEBUG
		// vec3_print(e.lightv);
		// vec3_print(sight.normalv);
		// vec3_print(e.reflectv);
		// vec3_print(sight.eyev);
	e.reflect_dot_eye = vec3_prod(e.reflectv, sight.eyev);
	//DEBUG
		// if (e.reflect_dot_eye > 0)
		// 	printf("e.reflect_dot_eye %.02f\n", e.reflect_dot_eye);
	if (e.reflect_dot_eye <= 0)
		specular = color_new(0, 0, 0);
	else
	{
		//6.compute the specular contribution
		e.factor = powf(e.reflect_dot_eye, m.shininess);

		//DEBUG
			if ((0) && e.factor > 0)
			{
				printf("m.shininess %.02f\n", m.shininess);
				printf("e.reflect_dot_eye %.02f\n", e.reflect_dot_eye);
				printf("e.factor %.08f\n", e.factor);
			}

		specular = color_multiply(light.intensity, m.specular * e.factor);
	}

	//DEBUG
	if (0)
	{
		printf("\n== DEBUG in LIGHT EXPOSURE ==\n");
		if(light.intensity.red > 0.01|| light.intensity.blue > 0.01|| light.intensity.green > 0.01)
		{
			printf("light.intensity: ");
			color_print(light.intensity);
		}	
		printf("m.ambient ");
		color_print(m.ambient);
		printf("e.effective_color ");
		color_print(e.effective_color);
		printf("ambient ");
		color_print(ambient);
		printf("diffuse ");
		color_print(ambient);
		if (specular.blue > 0 | specular.green > 0 | specular.red > 0)
		{
			printf("specular \n");
			color_print(specular);
		}
		// printf("result ");
		// color_print(color_add(color_add(ambient, diffuse), specular));	
	}

	// Add the three contributions together to get the final shading
	return (color_add(color_add(ambient, diffuse), specular));
}



