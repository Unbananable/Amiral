/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_placement_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:08:38 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/07 14:34:23 by dtrigalo         ###   ########.fr       */
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
	X_OFFSET = nearbyint((WIN_WIDTH - ((XMAX - XMIN) * SCALE)) / 2
			- XMIN * SCALE);
	Y_OFFSET = nearbyint((WIN_HEIGHT - ((YMAX - YMIN) * SCALE)) / 2
			- YMIN * SCALE);
}
