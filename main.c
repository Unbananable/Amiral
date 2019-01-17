/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 17:51:55 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/17 18:01:12 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib>
#include "libft/libft.h"

void	usage(void)
{
	ft_putstr("usage: ./fdf map_filename");
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

	return (0);
}
