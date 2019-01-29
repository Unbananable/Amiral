/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:10:25 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/29 12:35:26 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

int		new_image(t_fdf *fdf)
{
	if (!(fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, WIN_WIDTH, WIN_HEIGHT)))
		return (0);
	if (!(fdf->addr = (unsigned int *)mlx_get_data_addr(fdf->img_ptr,
			&(fdf->image.bpp), &(fdf->image.size_line), &(fdf->image.endian))))
		return (0);
	return (1);
}
