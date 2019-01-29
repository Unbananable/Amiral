/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 12:09:56 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/29 10:38:04 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "mlx.h"

void	free_array_array(void ***arrarr, int len)
{
	int		i;

	if (*arrarr)
	{
		i = -1;
		while (++i < len)
		{
			free(*arrarr[i]);
			*arrarr[i] = NULL;
		}
	}
	free(*arrarr);
	*arrarr = NULL;
}

void	clear_fdf(t_fdf *fdf)
{
	free(fdf->addr);
	free_array_array(&(fdf->map), fdf->map_info.depth);
	if (fdf->img_ptr)
		mlx_destroy_image(fdf->mlx_ptr, fdf->image_ptr);
	free(mlx_ptr);
	free(win_ptr);
	free_array_array(&(fdf->proj_map), fdf->map_info.depth);
}

void	error(char *str, t_fdf *fdf)
{
	ft_putstr(str);
	ft_putchar('\n');
	clear_fdf(fdf);
	exit(0);
}
