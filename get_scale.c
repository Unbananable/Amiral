/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:39:46 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/18 16:49:07 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	get_scale(t_point **proj_map, t_map *map_info)
{
	int		tmp;

	map_info->xmax = proj_map[map_info->depth - 1][map_info->width - 1].x;
	map_info->ymax = proj_map[0][0].y;
	map_info->scale = nearbyint((WIN_WIDTH - 2 * MARGIN) / map_info->xmax);
	tmp = nearbyint((WIN_HEIGHT - 2 * MARGIN) / map_info->ymax);
	map_info->scale = (tmp < map_info->scale) ? tmp : map_info->scale;
}
