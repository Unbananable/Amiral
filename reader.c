/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 14:03:04 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/22 20:01:03 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TO DO
 * - Gestion des erreurs (fuites memoires, etc.)
*/

#include <stdlib.h>
#include "libft/includes/libft.h"
#include "fdf.h"
#include <fcntl.h>
#include "get_next_line.h"

#include <stdio.h>

static int	get_width(char *line)
{
	int		res;
	int		i;

	i = 0;
	res = 0;
	while (line[i])
		if (ft_isdigit(line[i]))
		{
			res++;
			while (line[i] && ft_isdigit(line[i]))
				i++;
		}
		else
			i++;
	return (res);
}

static int	is_int(char *str)
{
	int		i;
	int		nb;
	int		is_neg;

	nb = ft_atoi(str);
	is_neg = (nb < 0 || (nb == 0 && str[0] == '-')) ? 1 : 0;
	i = 0 + is_neg;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (--i >= 0 && nb)
	{
		if (str[i] - '0' != ft_abs(nb % 10))
			return (0);
		nb /= 10;
	}
	while (i >= 0 && (str[i] == '0' || str[i] == ' '))
		i--;
	if ((!is_neg && str[i] == '-') || (is_neg && str[i] != '-'))
		return (0);
	i = (is_neg && str[i] == '-') ? i - 1 : i;
	while (i >= 0 && (str[i] == ' '))
		i--;
	return ((!nb && i == -1));
}

static int	*get_alts(char *line, t_map *map_info)
{
	int		*res;
	int		i;
	int		j;
	
	if (!(res = (int *)malloc(sizeof(int) * map_info->width)))
		error("MALLOC CACA");
	i = 0;
	j = 0;
	while (j < map_info->width && line[i])
		if (ft_isdigit(line[i]) || line[i] == '-')
		{
			if (is_int(line + i))
			{
				if((res[j++] = ft_atoi(line + i)) > map_info->zmax)
					map_info->zmax = res[j - 1];
				map_info->zmin = (res[j - 1] < map_info->zmin) ? res[j - 1] : map_info->zmin;
				while (line[i] && line[i] != ' ' && line[i] != '\t')
					i++;
			}
			else
				error("Z NON INT");
		}
		else if (line[i] != ' ' && line[i] != '\t')
			error("CHAR INVALID SUR LA MAP");
		else
			i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] || j != map_info->width)
		error("LARGEUR INVALIDE");
	return (res);
}

int			**reader(char *file_name, t_map *map_info)
{
	int		fd;
	char	*line;
	int		**res;
	int		i;

	map_info->zmax = 0;
	map_info->zmin = 0;
	if ((fd = open(file_name, O_RDONLY)) == -1)
		error("BAD OUVERTURE DE FICHIER");
	if(get_next_line(fd, &line))
		i = 1;
	else
		return (NULL);
	map_info->width = get_width(line);
	if (!(res = (int **)malloc(sizeof(int *) * map_info->depth)))
		error("MALLOC FOIREUX");
	res[map_info->depth - 1] = get_alts(line, map_info);
	free(line);
int ret;
	while ((ret = get_next_line(fd, &line)))
	{
		i++;
		res[map_info->depth - i] = get_alts(line, map_info);
		free(line);
	}
	close(fd);
	return (res);
}
