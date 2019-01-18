/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 17:51:55 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/18 12:09:48 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		deal_key(int key, void *param)
{
//Action qui se déroule à chaque input clavier (on peut par exemple print la
//touche (key) utilisée et s'en servir pour la relier à des actions définies
	key +=0;
	param +=0;
	return (0);
}

void	usage(void)
{
	ft_putstr("usage: ./fdf map_filename\n");
	exit(0);
}

int		main(int ac, char **av)
{
	int		**map;
	t_point **proj_map;
	t_map	map_info;
	void	*mlx_ptr;
	void	*win_ptr;

	if (ac != 2)
		usage();
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIN_HEIGHT, WIN_WIDTH, "FdF");
	map = reader(av[1], &map_info);
	proj_map = projection(map, map_info);
	draw_projection(proj_map, map_info);
	mlx_loop(mlx_ptr);
	return (0);
}
