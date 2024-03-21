/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:29:09 by thibault          #+#    #+#             */
/*   Updated: 2024/03/05 14:50:55 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

typedef struct s_canevas t_canevas;

typedef struct s_matrix
{
	double	mx[4][4];
	int		dim;
}	t_matrix;

typedef struct s_shearing
{
	double	p1;
	double	p2;
}	t_shearing;

/*matrix_op.c*/
t_matrix	mx_create(double mx_tab[MAX_DIM][MAX_DIM], int dimension);
void		mx_print(t_matrix mx);
t_matrix	mx_mx_multiply(t_matrix m1, t_matrix m2);
t_vec3		mx_vec3_multiply(t_matrix m, t_vec3 v);
t_matrix	mx_transpose(t_matrix m);
t_matrix	mx_identity_matrix(void);

double mx_get_minor(t_matrix m, int li, int col);
double	mx_get_cofactor(t_matrix m, int li, int col);
double	mx_get_deter(t_matrix m);
t_matrix	mx_inverse(t_matrix m);

t_matrix	mx_translation(double x, double y, double z);
t_matrix	mx_scaling(double x, double y, double z);
t_matrix	mx_x_rotation(double radian);
t_matrix	mx_y_rotation(double radian);
t_matrix	mx_z_rotation(double radian);
t_matrix	mx_translation(double x, double y, double z);

t_matrix	mx_shearing(t_shearing x, t_shearing y, t_shearing z);


int			mx_tester(t_canevas *cnv);

// t_matrix	mx_mx_add(t_matrix m1, t_matrix m2);
// t_matrix	mx_mx_scalar_multiply(t_matrix m1, double scalar);
// t_matrix	mx_mx_substr(t_matrix m1, t_matrix m2);
#endif
