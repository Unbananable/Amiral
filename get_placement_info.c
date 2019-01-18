/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_placement info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:39:46 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/18 18:07:58 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

#include <stdio.h>

void	get_placement_info(t_point **proj_map, t_map *map_info)
{
	int		tmp;
	double	xmax;
	double	ymax;

	map_info->scale = nearbyint((WIN_WIDTH - 2 * MARGIN) / map_info->xmax);
	tmp = nearbyint((WIN_HEIGHT - 2 * MARGIN) / map_info->ymax);
	map_info->scale = (tmp < map_info->scale) ? tmp : map_info->scale;
	map_info->x_offset = nearbyint((WIN_WIDTH - (map_info->xmax * map_info->scale)) / 2);
	map_info->y_offset = nearbyint((WIN_HEIGHT - (map_info->ymax * map_info->scale)) / 2);
}
