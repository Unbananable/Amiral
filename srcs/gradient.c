/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:11:03 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/07 16:49:30 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	percent(double current, double start, double end)
{
	return ((current - start) / (end - start));
}

int		color_lvl(int start, int end, double ratio)
{
	return ((int)((1 - ratio) * start + ratio * end));
}

int		gradient(t_fdf *fdf, t_point p, t_point p1, t_point p2)
{
	double	ratio;
	int		red;
	int		green;
	int		blue;

	ratio = (p2.x - p1.x > p2.y - p1.y) ?
		percent(p.x, p1.x * SCALE + X_OFFSET, p2.x * SCALE + X_OFFSET)
		: percent(p.y, p1.y * SCALE + Y_OFFSET, p2.y * SCALE + Y_OFFSET);
	red = color_lvl((p1.color >> 16) & 0xFF, (p2.color >> 16) & 0xFF, ratio);
	green = color_lvl((p1.color >> 8) & 0xFF, (p2.color >> 8) & 0xFF, ratio);
	blue = color_lvl(p1.color & 0xFF, p2.color & 0xFF, ratio);
	return ((red << 16) | (green << 8) | blue);
}
