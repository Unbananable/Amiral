/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 11:32:15 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/01 12:32:53 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void		event_rainbow(t_fdf *fdf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < DEPTH)
	{
		j = -1;
		while (++j < WIDTH)
		{
			if (fdf->proj_map[i][j].colour & 0xFF0000
					&& fdf->proj_map[i][j].colour & 0x00FF00
					&& fdf->proj_map[i][j].colour & 0x0000FF)
				fdf->proj_map[i][j].colour = 0xFF0000;
			else if (fdf->proj_map[i][j].colour & 0xFF0000
					&& !(fdf->proj_map[i][j].colour & 0x0000FF))
			{
				fdf->proj_map[i][j].colour -= 0x050000;
				fdf->proj_map[i][j].colour += 0x000500;
			}
			else if (fdf->proj_map[i][j].colour & 0x00FF00
					&& !(fdf->proj_map[i][j].colour & 0xFF0000))
			{
				fdf->proj_map[i][j].colour -= 0x000500;
				fdf->proj_map[i][j].colour += 0x000005;
			}
			else if (fdf->proj_map[i][j].colour & 0x0000FF
					&& !(fdf->proj_map[i][j].colour & 0x00FF00))
			{
				fdf->proj_map[i][j].colour -= 0x000005;
				fdf->proj_map[i][j].colour += 0x050000;
			}
		}
	}
}
