/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:50:10 by thibault          #+#    #+#             */
/*   Updated: 2024/03/05 14:50:55 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix mx_create(double mx_tab[MAX_DIM][MAX_DIM], int dimension)
{
	t_matrix	new_mx;

	new_mx.dim = dimension;
	ft_memmove(new_mx.mx, mx_tab, sizeof(double) * SIZE_MATRIX);
	return (new_mx);

}

t_shearing mx_shearing_create(double param1, double param2)
{
	t_shearing	new_shearing;

	new_shearing.p1 = param1;
	new_shearing.p2 = param2;
	return (new_shearing);
}


void mx_print(t_matrix mx)
{
	int li, col;

	li = 0;
	while (li < mx.dim)
	{
		col = 0;
		while (col < mx.dim)
		{
			printf("%6.2f ", mx.mx[li][col]);
			col++;
		}
		printf("\n");
		li++;
	}
}

t_matrix	mx_mx_multiply(t_matrix m1, t_matrix m2)
{
	double	mxprod[MAX_DIM][MAX_DIM];
	int		li;
	int		col;
	
	ft_bzero(mxprod, sizeof(double) * SIZE_MATRIX);
	li = 0;
	while (li < 4)
	{
		col = 0;
		while (col < 4)
		{
			mxprod[li][col] = m1.mx[li][0] * m2.mx[0][col]
				+ m1.mx[li][1] * m2.mx[1][col]
				+ m1.mx[li][2] * m2.mx[2][col]
				+ m1.mx[li][3] * m2.mx[3][col];
			col++;
		}
		li++;
	}
	return (mx_create(mxprod ,MAX_DIM));
}


t_vec3	mx_vec3_multiply(t_matrix m, t_vec3 v)
{
	double		v_tab[MAX_DIM];
	t_vec3		v_result;
	int			li;
	
	
	li = 0;
	while (li < 4)
	{
		v_tab[li] = m.mx[li][0] * v.x
			+ m.mx[li][1] * v.y
			+ m.mx[li][2] * v.z
			+ m.mx[li][3] * v.w;
		li++;
	}
	v_result = vec3_create(v_tab[0], v_tab[1], v_tab[2], v_tab[3]);
	return (v_result);
}


t_matrix	mx_transpose(t_matrix m)
{
	double	mxprod[MAX_DIM][MAX_DIM];
	int		li;
	int		col;
	
	ft_bzero(mxprod, sizeof(double) * SIZE_MATRIX);
	li = 0;
	while (li < 4)
	{
		col = 0;
		while (col < 4)
		{
			mxprod[li][col] = m.mx[col][li];
			col++;
		}
		li++;
	}
	return (mx_create(mxprod ,MAX_DIM));
}

t_matrix	get_submatrix(t_matrix m, int li, int col)
{
	double	submx_tab[MAX_DIM][MAX_DIM];
	int		i;
	int		j;
	int		sub_i;
	int		sub_j;

	ft_bzero(submx_tab, sizeof(double) * SIZE_MATRIX);
	i = 0;
	sub_i = 0;
	while (i < m.dim) {
		if (i != li) {
			j = 0; sub_j = 0;
			while (j < m.dim)
			{
				if (j != col)
				{
					submx_tab[sub_i][sub_j] = m.mx[i][j];
					sub_j++;
				}
				j++;
			}
			sub_i++;
		}
		i++;
	}
	return (mx_create(submx_tab, m.dim - 1));
}


double mx_get_minor(t_matrix m, int li, int col)
{
	t_matrix submx;
	double minor;

	submx = get_submatrix(m, li, col);
	minor = mx_get_deter(submx);
	//DEBUG
		// printf("Submatrix:\n");
		// mx_print(submx);
		// printf("Minor: %.2f\n", minor);
	return (minor);
}


double	mx_get_cofactor(t_matrix m, int li, int col)
{
		int		sign;
		double	minor;
		
		sign = 1;
		minor = 0;
		if ((li + col) % 2)
			sign = -1;
		// printf("Sign: %d\n", sign);
		minor = mx_get_minor(m,li, col);
		return (sign * minor);
}

double	mx_get_deter(t_matrix m)
{
	double	det;
	int		col;

	col = 0;
	det = 0;
	if (m.dim == 2)
	{
		det = m.mx[0][0] * m.mx[1][1] - m.mx[0][1] * m.mx[1][0];
	}
	else
	{
		while (col < m.dim)
		{
			det = det + m.mx[0][col] * mx_get_cofactor(m, 0, col);
			col++;
		}
	}
	// printf("mx_get_deter: determinant: %-2f\n", det);
	return (det);
}

t_matrix	mx_identity_matrix(void)
{
	double	table_id[MAX_DIM][MAX_DIM] = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
	};

	return (mx_create(table_id, MAX_DIM));
}

t_matrix	mx_inverse(t_matrix m)
{
	double	mx_inv[MAX_DIM][MAX_DIM];
	int		li;
	int		col;
	double	cofactor;
	double	deter;
	
	deter = mx_get_deter(m);
	if (!deter)
		return (mx_identity_matrix());
	
	ft_bzero(mx_inv, sizeof(double) * SIZE_MATRIX);
	li = 0;
	while (li < m.dim)
	{
		col = 0;
		cofactor = 0;
		while (col < 4)
		{
			cofactor = mx_get_cofactor(m, li, col);
			//inversion de li, col -> col, li (= transposition)
			mx_inv[col][li] = cofactor / deter;
			col++;
		}
		li++;
	}
	return (mx_create(mx_inv ,MAX_DIM));
}

t_matrix	mx_translation(double x, double y, double z)
{
	double	transl[MAX_DIM][MAX_DIM] = {
	{1, 0, 0, x},
	{0, 1, 0, y},
	{0, 0, 1, z},
	{0, 0, 0, 1},
	};

	return (mx_create(transl, MAX_DIM));
}

t_matrix	mx_scaling(double x, double y, double z)
{
	 double	scale[MAX_DIM][MAX_DIM] = {
	{x, 0, 0, 0},
	{0, y, 0, 0},
	{0, 0, z, 0},
	{0, 0, 0, 1},
	};

	return (mx_create(scale, MAX_DIM));
}

t_matrix mx_x_rotation(double radian)
{
	double	rot_x[MAX_DIM][MAX_DIM];
	double	sinus;
	double	cosinus;

	ft_bzero(rot_x, sizeof(double) * SIZE_MATRIX);
	sinus = sin(radian);
	cosinus = cos(radian);
	rot_x[0][0] = 1;
	rot_x[1][1] = cosinus;
	rot_x[1][2] = -sinus;
	rot_x[2][1] = sinus;
	rot_x[2][2] = cosinus;
	rot_x[3][3] = 1;
	return (mx_create(rot_x, MAX_DIM));
}

t_matrix mx_y_rotation(double radian)
{
	double	rot_y[MAX_DIM][MAX_DIM];
	double	sinus;
	double	cosinus;

	ft_bzero(rot_y, sizeof(double) * SIZE_MATRIX);
	sinus = sin(radian);
	cosinus = cos(radian);
	rot_y[0][0] = cosinus;
	rot_y[0][2] = sinus;
	rot_y[1][1] = 1;
	rot_y[2][0] = -sinus;
	rot_y[2][2] = cosinus;
	rot_y[3][3] = 1;
	return (mx_create(rot_y, MAX_DIM));
}

t_matrix mx_z_rotation(double radian)
{
	double	rot_z[MAX_DIM][MAX_DIM];
	double	sinus;
	double	cosinus;
	
	ft_bzero(rot_z, sizeof(double) * SIZE_MATRIX);
	sinus = sin(radian);
	cosinus = cos(radian);
	rot_z[0][0] = cosinus;
	rot_z[0][1] = -sinus;
	rot_z[1][0] = sinus;
	rot_z[1][1] = cosinus;
	rot_z[2][2] = 1;
	rot_z[3][3] = 1;
	return (mx_create(rot_z, MAX_DIM));
}

t_matrix	mx_shearing(t_shearing x, t_shearing y, t_shearing z)
{
	double	mx_shear[MAX_DIM][MAX_DIM];
	ft_bzero(mx_shear, sizeof(double) * SIZE_MATRIX);
	mx_shear[0][0] = 1;
	mx_shear[0][1] = x.p1;
	mx_shear[0][2] = x.p2;
	mx_shear[1][0] = y.p1;
	mx_shear[1][1] = 1;
	mx_shear[1][2] = y.p2;
	mx_shear[2][0] = z.p1;
	mx_shear[2][1] = z.p2;
	mx_shear[2][2] = 1;
	mx_shear[3][3] = 1;
	return (mx_create(mx_shear, MAX_DIM));
}

int	mx_tester(t_canevas *cnv)
{
	// t_matrix	m1;
	// t_matrix	m2;
	// t_matrix	mx_result;
	// t_matrix	mx_shear;
	// t_vec3		v_result;
	// t_vec3		v_point;
	// t_vec3		v_init;
	// double		result;
	// t_sphere	sphere;
	// t_discriminant		discr;
	// t_ray		ray;
	// t_ray		new_ray;
	// t_shearing x_shear = {0, 0};
	// t_shearing y_shear = {0, 0};
	// t_shearing z_shear = {0, 1};
	// // double		tab1[MAX_DIM][MAX_DIM] = {
	// // {8, -5, 9, 2},
	// // {7, 5, 6, 1},
	// // {-6, 0, 9, 6},
	// // {-3, 0, -9, -4},
	// // };
	// double	tab1[MAX_DIM][MAX_DIM] = {
	// {9, 3, 0, 9},
	// {-5, -2, -6, -3},
	// {-4, 9, 6, 4},
	// {-7, 6, 6, 2},
	// };
	// double		tab2[MAX_DIM][MAX_DIM] = {
	// {2, 0, 0, 1},
	// {0, 2, 0, 0},
	// {0, 0, 2, 0},
	// {0, 0, 0, 2},
	// };
	//Detrminant = 0
	// double		tab1[MAX_DIM][MAX_DIM] = {
	// {-4, 2, -2, -3},
	// {-9, 6, 2, 6},
	// {0, -5, 1, -5},
	// {0, 0, 0, 0},
	// };
	// v_point = vec3_create(1, 2, 3 , 1);
	// v_init = vec3_create(0, 1, 0, 0);
	// v_result = vec3_create(-10, 0, 0, 0);
	// ray = ray_create(v_point, v_init);
	// sphere = sphere_create(v_point, 5);
	// discr = ray_sphere_intersect(ray, sphere);
	// m1 = mx_create(tab1, 4);
	// m2 = mx_create(tab2, MAX_DIM);
	// (void)m2;
	// mx_result = mx_mx_multiply(m1, m2);
	// mx_result = mx_transpose(m2);
	// mx_shear = mx_shearing(x_shear, y_shear, z_shear);
	// v_result = mx_vec3_multiply(mx_z_rotation(M_PI_4), v_init);
	// v_result = mx_vec3_multiply(mx_shear, v_init);
	// v_result = ray_get_point(ray_create(v_point, v_init), 2);
	// result = mx_get_deter(m1);
	// mx_result = mx_inverse(m1);
	// mx_result = mx_mx_multiply(m1, mx_result);
	// m1 = mx_inverse(mx_translation(3, 4, 5));
	// new_ray = ray_transform(ray, mx_translation(3, 4, 5));
	// new_ray = ray_transform(ray, mx_scaling(2, 3, 4));
	if (cnv->debug_mode)
	{
		// printf("\n== DEBUG MODE in mx_tester ==\n");
		// printf("m1:\n");
		// mx_print(m1);
		// printf("mx_result:\n");
		// mx_print(mx_result);
		// printf("mx_result:\n");
		// mx_print(mx_result);
		// printf("\nv_init:\n");
		// vec3_print(v_init);
		// printf("mx_x_rotation:\n");
		// mx_print(mx_x_rotation(M_PI_4));
		// printf("\nv_result:\n");
		// vec3_print(v_result);
		// printf("\ndeter m1: %.2f\n", result);
		// printf("\ndeter sphere: %.2f\n", discr.discr);
		// printf("t1 = %.2f, t2 = %.2f\n\n", discr.t1, discr.t2);
		// printf("m1:\n");
		// mx_print(m1);
		// ray_print(ray);
		// ray_print(new_ray);
		
	}
	return (0);
}

// t_matrix	mx_mx_scalar_multiply(t_matrix m1, double scalar)
// {
// 	double	mxprod[MAX_DIM][MAX_DIM];
// 	int		li;
// 	int		col;
	
// 	ft_bzero(mxprod, sizeof(double) * SIZE_MATRIX);
// 	li = 0;
// 	while (li < 4)
// 	{
// 		col = 0;
// 		while (col < 4)
// 		{
// 			mxprod[li][col] = m1.mx[li][col] * scalar;
// 			col++;
// 		}
// 		li++;
// 	}
// 	return (mx_create(mxprod ,MAX_DIM));
// }

// t_matrix	mx_mx_add(t_matrix m1, t_matrix m2)
// {
// 	double	mxprod[MAX_DIM][MAX_DIM];
// 	int		li;
// 	int		col;
	
// 	ft_bzero(mxprod, sizeof(double) * SIZE_MATRIX);
// 	li = 0;
// 	while (li < 4)
// 	{
// 		col = 0;
// 		while (col < 4)
// 		{
// 			mxprod[li][col] = m1.mx[li][col] + m2.mx[li][col];
// 			col++;
// 		}
// 		li++;
// 	}
// 	return (mx_create(mxprod ,MAX_DIM));
// }

// t_matrix	mx_mx_substr(t_matrix m1, t_matrix m2)
// {
// 	double	mxprod[MAX_DIM][MAX_DIM];
// 	int		li;
// 	int		col;
	
// 	ft_bzero(mxprod, sizeof(double) * SIZE_MATRIX);
// 	li = 0;
// 	while (li < 4)
// 	{
// 		col = 0;
// 		while (col < 4)
// 		{
// 			mxprod[li][col] = m1.mx[li][col] - m2.mx[li][col];
// 			col++;
// 		}
// 		li++;
// 	}
// 	return (mx_create(mxprod ,MAX_DIM));
// }