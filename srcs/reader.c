/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 14:03:04 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/29 17:30:40 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fdf.h"
#include <fcntl.h>

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

static int	get_alt(int *alt, t_file *stream)
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
	if (tmp == '-' && *alt == 0 && sign == 1 && (sign = -1))
		if ((tmp = ft_fgetc(stream)) > '9' || tmp < '0')
			return (0);
	while (tmp >= '0' && tmp <= '9')
	{
		if (!add_if_int(alt, tmp - '0', sign))
			return (0);
		tmp = ft_fgetc(stream);
	}
	if (tmp != ' ' && tmp != '\t' && tmp != '\n' && tmp != -1)
		return (0);
	*alt = (*alt > 0) ? *alt * sign : *alt;
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
	while (++i < fdf->map_info.depth && (j = -1))
		while (++j < fdf->map_info.width && !(fdf->map[i][j] = 0))
			if (!get_alt(&(fdf->map[i][j]), stream))
			{
				ft_fclose(stream);
				return (0);
			}
	while ((i = ft_fgetc(stream)) == ' ' || i == '\t' || i == '\n')
		;
	ft_fclose(stream);
	if (i != -1)
		return (0);
	return (1);
}
