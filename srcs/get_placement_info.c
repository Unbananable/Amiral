/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_placement_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:08:38 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/28 16:39:24 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	get_placement_info(t_point **proj_map, t_map *map_info)
{
	double		tmp;

	SCALE = (WIN_WIDTH - 2 * MARGIN) / (XMAX - XMIN);
	tmp = (WIN_HEIGHT - 2 * MARGIN) / (YMAX - YMIN);
	SCALE = (tmp < SCALE) ? tmp : SCALE;
	map_info->x_offset = nearbyint((WIN_WIDTH - ((XMAX - XMIN) * SCALE)) / 2
			- XMIN * SCALE);
	map_info->y_offset = nearbyint((WIN_HEIGHT - ((YMAX - YMIN) * SCALE)) / 2
			- YMIN * SCALE);
	map_info->alt_ratio = 1.0;
}
