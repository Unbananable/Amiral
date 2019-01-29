/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_placement_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:08:38 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/29 17:33:39 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	get_placement_info(t_fdf *fdf)
{
	double		tmp;

	SCALE = (WIN_WIDTH - 2 * MARGIN) / (XMAX - XMIN);
	tmp = (WIN_HEIGHT - 2 * MARGIN) / (YMAX - YMIN);
	SCALE = (tmp < SCALE) ? tmp : SCALE;
	fdf->map_info.x_offset = nearbyint((WIN_WIDTH - ((XMAX - XMIN) * SCALE)) / 2
			- XMIN * SCALE);
	fdf->map_info.y_offset = nearbyint((WIN_HEIGHT - ((YMAX - YMIN) * SCALE)) / 2
			- YMIN * SCALE);
	fdf->map_info.alt_ratio = 1.0;
}
