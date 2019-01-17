/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 17:51:55 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/17 18:39:26 by dtrigalo         ###   ########.fr       */
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

	if (ac != 2)
		usage();
	map = reader(av[1], &map_info);
	proj_map = projection(map, map_info);
	draw_projection(proj_map, map_info);

/*	void	*mlx_ptr;
	void	*win_ptr;
	t_point p0;
	t_point p1;

	p0.x = 1;
	p0.y = 1;
	p1.x = 100;
	p1.y = 100;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Bonjour bonjour !!");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	draw_line(mlx_ptr, win_ptr, p0, p1);
	mlx_loop(mlx_ptr);*/
	return (0);
}
