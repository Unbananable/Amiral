/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 14:03:04 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/28 19:10:50 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fdf.h"
#include <fcntl.h>

#include <stdio.h>

static int	add_if_int(int *nb, int to_add, int sign)
{
	if (*nb > 214748364 || (*nb == 214748364
				&& (to_add > 8 || (to_add == 8 && sign == 1))))
		return (0);
	else if (*nb == 214748364 && to_add == 8 && sign == -1)
		*nb = -(*nb) * 10 - to_add;
	else
		*nb = *nb * 10 + to_add;
	return (1);
}

static int	get_alt(int *map, int j, t_file *stream, t_map *map_info)
{
	int		sign;
	int		tmp;

	if ((tmp = ft_fgetc(stream)) == -1)
		return (0);
	while ((sign = 1) && (tmp == ' ' || tmp == '\t'))
		tmp = ft_fgetc(stream);
	while (tmp != '\n' && tmp != ' ' && tmp != '\t' && tmp != -1)
	{
		if (tmp == '-' && map[j] == 0 && sign == 1)
			sign = -1;
		else if (tmp >= '0' && tmp <= '9')
		{
			if (!add_if_int(&(map[j]), tmp - '0', sign))
				return (0);
		}
		else
			return (0);
		tmp = ft_fgetc(stream);
	}
	if ((tmp == '\n' && j != WIDTH - 1) || (j == WIDTH - 1 && tmp != '\n'))
		return (0);
	map[j] = (map[j] > 0) ? map[j] * sign : map[j];
	return (1);
}

int			**reader(char *file_name, t_map *map_info)
{
	t_file	*stream;
	int		**res;
	int		i;
	int		j;

	if (!(stream = ft_fopen(file_name)))
		error("BAD STREAM");
	if (!(res = (int **)malloc(sizeof(int *) * DEPTH)))
		error("MALLOC FOIREUX");
	i = -1;
	while (++i < DEPTH)
	{
		if (!(res[i] = (int *)malloc(sizeof(int) * WIDTH)))
			error("MALLOC NUL");
		j = -1;
		while (++j < WIDTH && !(res[i][j] = 0))
			if (!get_alt(res[i], j, stream, map_info))
				error("BAD MAP");
	}
	if (ft_fgetc(stream) != -1)
		error("BAD MAP");
	ft_fclose(stream);
	return (res);
}
