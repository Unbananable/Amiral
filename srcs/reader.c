/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 14:03:04 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/08 15:32:56 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fdf.h"
#include <fcntl.h>

#include <stdio.h>

static int	add_if_int(int *nb, int to_add, int *sign)
{
	if (*nb > 214748364 || (*nb == 214748364
				&& (to_add > 8 || (to_add == 8 && *sign == 1))))
		return (0);
	else if (*nb == 214748364 && to_add == 8 && *sign == -1)
	{
		*nb = -(*nb) * 10 - to_add;
		*sign = 1;
	}
	else
		*nb = *nb * 10 + to_add;
	return (1);
}

static int	get_color(t_fdf *fdf, int x, int y, t_file *stream)
{
	char	hex_color[7];
	int		tmp;
	int		i;

	fdf->color_scheme = MAP;
	if ((tmp = ft_fgetc(stream)) != '0'
			|| ((tmp = ft_fgetc(stream)) != 'x' && tmp != 'X'))
		return (0);
	i = -1;
	while (++i < 6 && (((tmp = ft_fgetc(stream)) >= '0' && tmp <= '9')
				|| (tmp >= 'A' && tmp <= 'F') || (tmp >= 'a' && tmp <= 'f')))
		hex_color[i] = tmp;
	if (i == 6)
		tmp = ft_fgetc(stream);
	if (tmp != ' ' && tmp != -1 && tmp != '\n' && tmp != '\t')
		return (0);
	hex_color[i] = 0;
	if ((fdf->proj[y][x].color = ft_atoi_base(hex_color, 16)) == -1)
		return (0);
	return (1);
}

static int	get_alt(t_fdf *fdf, int x, int y, t_file *stream)
{
	int		sign;
	int		tmp;
	int		nl;

	nl = 0;
	if ((tmp = ft_fgetc(stream)) == -1)
		return (0);
	while ((sign = 1) && (tmp == ' ' || tmp == '\t' || (tmp == '\n' && !nl)))
	{
		nl = (tmp == '\n') ? 1 : 0;
		tmp = ft_fgetc(stream);
	}
	if (tmp == '-' && fdf->map[y][x] == 0 && sign == 1 && (sign = -1))
		if ((tmp = ft_fgetc(stream)) > '9' || tmp < '0')
			return (0);
	while (tmp >= '0' && tmp <= '9')
		if (!add_if_int(&fdf->map[y][x], tmp - '0', &sign))
			return (0);
		else
			tmp = ft_fgetc(stream);
	if (tmp == ',' && !get_color(fdf, x, y, stream))
		return (0);
	else if (tmp != ',' && tmp != ' ' && tmp != -1 && tmp != '\n'
			&& tmp != '\t')
		return (0);
	fdf->map[y][x] *= sign;
	return (1);
}

int			reader(char *file_name, t_fdf *fdf)
{
	t_file	*stream;
	int		i;
	int		j;

	if (!(stream = ft_fopen(file_name)))
		return (0);
	i = -1;
	while (++i < fdf->depth && (j = -1))
		while (++j < fdf->width && !(fdf->map[i][j] = 0))
		{
			fdf->proj[i][j].color = 0xFFFFFF;
			if (!get_alt(fdf, j, i, stream))
			{
				ft_fclose(stream);
				return (0);
			}
			if (i == 0 && j == 0)
			{
				fdf->zmax = fdf->map[0][0];
				fdf->zmin = fdf->zmax;
			}
			fdf->zmax = fdf->map[i][j] > fdf->zmax ? fdf->map[i][j] : fdf->zmax;
			fdf->zmin = fdf->map[i][j] < fdf->zmin ? fdf->map[i][j] : fdf->zmin;
		}
	while ((i = ft_fgetc(stream)) == ' ' || i == '\t' || i == '\n')
		;
	ft_fclose(stream);
	return ((i != -1) ? 0 : 1);
}
