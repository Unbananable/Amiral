/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:49:33 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/08 14:17:30 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "colors.h"

void	draw_point(t_fdf *fdf)
{
	t_point	p;

	p.x = fdf->x_offset;
	p.y = fdf->y_offset;
	if (fdf->color_scheme == MONO)
		p.color = 0xFFFFFF;
	else if (fdf->color_scheme == ALTITUDE)
		p.color = (fdf->map[0][0] < 0) ? SEA : LOW;
	else if (fdf->color_scheme == MAP)
		p.color = fdf->proj[0][0].color;
	else if (fdf->color_scheme == RAINBOW)
		p.color = 0xFF0000;
	else if (fdf->color_scheme == FANCY_RAINBOW)
		p.color = fdf->rainbow;
	fill_pixel(fdf, p);
}
