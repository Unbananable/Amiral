/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_placement_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:08:38 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/08 12:24:51 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	get_placement_info(t_fdf *fdf)
{
	double		tmp;

	if (fdf->width == 1 && fdf->depth == 1)
	{
		fdf->scale = 1;
		fdf->x_offset = WIN_WIDTH / 2;
		fdf->y_offset = WIN_HEIGHT / 2;
	}
	else
	{
		fdf->scale = (WIN_WIDTH - 2 * MARGIN)
			/ (fdf->xmax - fdf->xmin);
		tmp = (WIN_HEIGHT - 2 * MARGIN) / (fdf->ymax
				- fdf->ymin);
		fdf->scale = (tmp < fdf->scale) ?
			tmp : fdf->scale;
		fdf->x_offset = nearbyint((WIN_WIDTH - ((fdf->xmax
				- fdf->xmin) * fdf->scale)) / 2
				- fdf->xmin * fdf->scale);
		fdf->y_offset = nearbyint((WIN_HEIGHT - ((fdf->ymax
				- fdf->ymin) * fdf->scale)) / 2
				- fdf->ymin * fdf->scale);
	}
}
