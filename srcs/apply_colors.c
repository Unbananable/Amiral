/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:13:13 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/01 15:00:46 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	altitude_colors(t_fdf *fdf)
{
	fdf += 0;
	return ;
}

void		apply_colors(t_fdf *fdf)
{
	if (fdf->map_info.color_scheme == MONO)
		;
	else if (fdf->map_info.color_scheme == MAP)
		;
	else if (fdf->map_info.color_scheme == ALTITUDE)
		altitude_colors(fdf);
}
