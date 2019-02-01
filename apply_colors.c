/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:13:13 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/01 14:34:54 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	altitude_colors(fdf)
{
	return ;
}

void		apply_colors(t_fdf *fdf)
{
	if (fdf->map_info.color_scheme == MONO)
		;
	else if (fdf->map_info.color_scheme == MAP)
		;
	else_if (fdf->map_info.color_scheme == ALTITUDE)
		altitude_colors(fdf);
}
