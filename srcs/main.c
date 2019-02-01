/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 17:51:55 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/01 12:49:47 by dtrigalo         ###   ########.fr       */
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
	int		tmp;

	if (!(stream = ft_fopen(file_name)))
		return (-1);
	res = 0;
	tmp = ft_fgetc(stream);
	while (tmp != -1 && tmp != '\n')
	{
		while (tmp == ' ' || tmp == '\t')
			tmp = ft_fgetc(stream);
		if (tmp == '-' || (tmp >= '0' && tmp <= '9'))
			res++;
		while (tmp == '-' || (tmp >= '0' && tmp <= '9'))
			tmp = ft_fgetc(stream);
		if (tmp != '-' && tmp != ' ' && tmp != '\t' && (tmp < '0'
					|| tmp > '9') && tmp != -1 && tmp != '\n')
		{
			ft_fclose(stream);
			return (-1);
		}
	}
	ft_fclose(stream);
	return (res);
}

static void	init_map_info(t_map *map_info, char *file_path)
{
	if ((map_info->depth = ft_filelinecount(file_path)) == -1)
		error("error: invalid file", NULL);
	if ((map_info->width = get_width(file_path)) == -1)
		error("error: invalid file", NULL);
	if (map_info->depth == 0 || map_info->width == 0)
	{
		ft_putstr("error: empty map");
		exit(0);
	}
	map_info->alt_ratio = 1;
	map_info->proj = ISOMETRIC;
}

static int	init_fdf(t_fdf *fdf, char *file_path)
{
	int		i;

	init_map_info(&(fdf->map_info), file_path);
	fdf->addr = NULL;
	fdf->mlx_ptr = NULL;
	fdf->win_ptr = NULL;
	fdf->img_ptr = NULL;
	fdf->proj_map = NULL;
	if (!(fdf->map = (int **)malloc(sizeof(int *) * DEPTH)))
		return (0);
	i = -1;
	while (++i < DEPTH)
		if (!(fdf->map[i] = (int *)malloc(sizeof(int) * WIDTH)))
		{
			free_2d_int_tab(&(fdf->map), i);
			return (0);
		}
	if (!(fdf->proj_map = (t_point **)malloc(sizeof(t_point *) * DEPTH)))
		return (0);
	i = -1;
	while (++i < DEPTH)
		if (!(fdf->proj_map[i] = (t_point *)malloc(sizeof(t_point) * WIDTH)))
		{
			free_2d_tpoint_tab(&(fdf->proj_map), i);
			return (0);
		}
	return (1);
}

static void	usage(void)
{
	ft_putstr("usage: ./fdf map_filename\n");
	exit(0);
}

int			main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac != 2)
		usage();
	if (!(init_fdf(&fdf, av[1])))
		error("error: failed to initialize", &fdf);
	if (!(fdf.mlx_ptr = mlx_init()))
		error("error: failed to establish connection with the display", &fdf);
	if (!(fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, WIN_HEIGHT, WIN_WIDTH,
					"FdF")))
		error("error: failed to create window", &fdf);
	if (!reader(av[1], &fdf))
		error("error: map error", &fdf);
	if (!projection(&fdf))
		error("error: failed to create projection", &fdf);
	get_placement_info(&fdf);
	if (!new_image(&fdf))
		error("error: failed to create image", &fdf);
	draw_image(&fdf);
	command_menu(fdf);
	mlx_hook(fdf.win_ptr, 2, 0, &key_press, &fdf);
	mlx_hook(fdf.win_ptr, 3, 0, &key_release, &fdf);
	mlx_hook(fdf.win_ptr, 17, 0, &red_cross_closing, &fdf);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
