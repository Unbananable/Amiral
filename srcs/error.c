/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 12:09:56 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/08 14:26:29 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "mlx.h"
#include "fdf.h"

void	free_2d_int_tab(int ***tab, int len)
{
	int		i;

	if (*tab)
	{
		i = -1;
		while (++i < len)
		{
			free((*tab)[i]);
			(*tab)[i] = NULL;
		}
	}
	free(*tab);
	*tab = NULL;
}

void	free_2d_tpoint_tab(t_point ***tab, int len)
{
	int		i;

	if (*tab)
	{
		i = -1;
		while (++i < len)
		{
			free((*tab)[i]);
			(*tab)[i] = NULL;
		}
	}
	free(*tab);
	*tab = NULL;
}

void	clear_fdf(t_fdf *fdf)
{
	if (!fdf)
		return ;
	free_2d_int_tab(&(fdf->map), fdf->depth);
	if (fdf->mlx_ptr && fdf->img_ptr)
	{
		mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
		fdf->img_ptr = NULL;
	}
	fdf->addr = NULL;
	if (fdf->mlx_ptr && fdf->win_ptr)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		fdf->win_ptr = NULL;
	}
	free_2d_tpoint_tab(&(fdf->proj), fdf->depth);
}

void	error(char *str, t_fdf *fdf)
{
	ft_putstr(str);
	ft_putchar('\n');
	clear_fdf(fdf);
	exit(0);
}
