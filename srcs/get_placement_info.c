/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_placement_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:08:38 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/07 18:53:39 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	get_placement_info(t_fdf *fdf)
{
	double		tmp;

	if (fdf->map_info.width == 1 && fdf->map_info.depth == 1)
	{
		fdf->map_info.scale = 1;
		fdf->map_info.x_offset = WIN_WIDTH / 2;
		fdf->map_info.y_offset = WIN_HEIGHT / 2;
	}
	else
	{
		fdf->map_info.scale = (WIN_WIDTH - 2 * MARGIN)
			/ (fdf->map_info.xmax - fdf->map_info.xmin);
		tmp = (WIN_HEIGHT - 2 * MARGIN) / (fdf->map_info.ymax
				- fdf->map_info.ymin);
		fdf->map_info.scale = (tmp < fdf->map_info.scale) ?
			tmp : fdf->map_info.scale;
		fdf->map_info.x_offset = nearbyint((WIN_WIDTH - ((fdf->map_info.xmax
				- fdf->map_info.xmin) * fdf->map_info.scale)) / 2
				- fdf->map_info.xmin * fdf->map_info.scale);
		fdf->map_info.y_offset = nearbyint((WIN_HEIGHT - ((fdf->map_info.ymax
				- fdf->map_info.ymin) * fdf->map_info.scale)) / 2
				- fdf->map_info.ymin * fdf->map_info.scale);
	}
}
