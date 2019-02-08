/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 17:51:55 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/08 16:02:22 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "fdf.h"
#include "libft.h"

static int	get_width(char *file_name)
{
	int		res;
	t_file	*stream;
	int		t;

	if (!(stream = ft_fopen(file_name)))
		return (-1);
	res = 0;
	t = ft_fgetc(stream);
	while (t != -1 && t != '\n')
	{
		while (t == ' ' || t == '\t')
			t = ft_fgetc(stream);
		(t == '-' || (t >= '0' && t <= '9')) ? res++ : 0;
		while (is_valid_mapchar(t) && t != ' ' && t != '\n' && t != '\t')
			t = ft_fgetc(stream);
		if (!is_valid_mapchar(t))
		{
			ft_fclose(stream);
			return (-1);
		}
	}
	ft_fclose(stream);
	return (res);
}

static void	init_map_info_extra(t_fdf *fdf, char *file_path)
{
	if ((fdf->depth = ft_filelinecount(file_path)) == -1)
		error("error: invalid file", NULL);
	if ((fdf->width = get_width(file_path)) == -1)
		error("error: invalid file", NULL);
	if (fdf->depth == 0 || fdf->width == 0)
	{
		ft_putstr("error: map error\n");
		exit(0);
	}
	fdf->alt_ratio = 1.0;
	fdf->proj_type = PARALLEL;
	fdf->color_scheme = MONO;
	fdf->addr = NULL;
	fdf->mlx_ptr = NULL;
	fdf->win_ptr = NULL;
	fdf->img_ptr = NULL;
	fdf->proj = NULL;
	fdf->rainbow = 0xFF0000;
	fdf->printed = 0;
}

static int	init_fdf(t_fdf *fdf, char *file_path)
{
	int		i;

	init_map_info_extra(fdf, file_path);
	if (!(fdf->map = (int **)malloc(sizeof(int *) * fdf->depth)))
		return (0);
	i = -1;
	while (++i < fdf->depth)
		if (!(fdf->map[i] = (int *)malloc(sizeof(int) * fdf->width)))
		{
			free_2d_int_tab(&(fdf->map), i);
			return (0);
		}
	if (!(fdf->proj = (t_point **)malloc(sizeof(t_point *) * fdf->depth)))
		return (0);
	i = -1;
	while (++i < fdf->depth)
		if (!(fdf->proj[i] = (t_point *)malloc(sizeof(t_point) * fdf->width)))
		{
			free_2d_tpoint_tab(&(fdf->proj), i);
			return (0);
		}
	return (1);
}

static void	hooks(t_fdf fdf)
{
	mlx_hook(fdf.win_ptr, 2, 0, &key_press, &fdf);
	mlx_hook(fdf.win_ptr, 3, 0, &key_release, &fdf);
	mlx_hook(fdf.win_ptr, 4, 0, &mouse_press, &fdf);
	mlx_hook(fdf.win_ptr, 5, 0, &mouse_release, &fdf);
	mlx_hook(fdf.win_ptr, 6, 0, &mouse_move, &fdf);
	mlx_hook(fdf.win_ptr, 17, 0, &red_cross_closing, &fdf);
	mlx_loop(fdf.mlx_ptr);
}

int			main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac != 2)
	{
		ft_putstr("usage: ./fdf map_filename\n");
		exit(0);
	}
	if (!(init_fdf(&fdf, av[1])))
		error("error: failed to initialize", &fdf);
	if (!reader(av[1], &fdf))
		error("error: map error", &fdf);
	if (!(fdf.mlx_ptr = mlx_init()))
		error("error: failed to initialize mlx connection", &fdf);
	if (!(fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIN_HEIGHT, WIN_WIDTH,
					"FdF")))
		error("error: mlx failure", &fdf);
	if (!projection(&fdf))
		error("error: failed to create projection", &fdf);
	get_placement_info(&fdf);
	if (!new_image(&fdf))
		error("error: failed to create image", &fdf);
	draw_image(&fdf);
	print_command_menu(fdf);
	hooks(fdf);
	return (0);
}
