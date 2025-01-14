/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 23:36:33 by kostya            #+#    #+#             */
/*   Updated: 2021/10/02 17:44:47 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include "global.h"

static int	__recursive_color_compute_julia_extension(const t_params *restrict params,
		FLOAT real, FLOAT imag) __attribute__((warn_unused_result));

int	julia_1(const FLOAT *restrict field_real,
	const FLOAT *restrict field_imag, t_data *restrict data)
{
	register FLOAT	real;
	register FLOAT	imag;
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < data->res_y)
	{
		x = 0;
		while (x < data->res_x)
		{
			real = field_real[x];
			imag = field_imag[y];
			put_pixel(data, (int)x, (int)y,
				__recursive_color_compute_julia_extension(data->params,
					real, imag));
			++x;
		}
		++y;
	}
	return (0);
}

static inline int	__recursive_color_compute_julia_extension(
	const t_params *restrict params, FLOAT real, FLOAT imag)
{
	unsigned int	req;
	register FLOAT	real_sq;
	register FLOAT	imag_sq;
	register FLOAT	abs;

	abs = 0;
	req = 0;
	real_sq = real * real;
	imag_sq = imag * imag;
	while (req < params->recursion_depth)
	{
		imag = 2 * real * imag + params->c_imag;
		real = real_sq - imag_sq + params->c_real;
		real_sq = real * real;
		imag_sq = imag * imag;
		abs = real_sq + imag_sq;
		if (abs > params->out_radius_sq)
			return (params->palette((FLOAT)req / params->recursion_depth, 0, 0));
		++req;
	}
	return ((int)(abs * 255));
}
