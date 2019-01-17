/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 14:03:04 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/17 14:53:21 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TO DO
 * - gestion des altitudes negatives
 * - Checker la conformite de la map
 * - Gestion des erreurs (fuites memoires, etc.)
*/

#include <stdlib.h>
#include "libft.h"

static int	get_width(char *line)
{
	int		res;
	int		i;

	i = -1;
	res = 0;
	while (line[++i])
		if (ft_isdigit(line[i]))
		{
			res++;
			while (line[i] && ft_isdigit(line[i]))
				i++;
		}
	}
	return (res);
}

static int *get_alts(char *line, int len)
{
	int		*res;
	int		i;
	int		j;
	
	if (!(res = (int *)malloc(sizeof(int) * len)))
		error();
	i = -1;
	j = 0;
	while (line[++i])
		if (ft_isdigit(line[i]))
		{
			res[j++] = ft_atoi(line + i);
			while (line[i] && ft_isdigit(line[i]))
				i++;
		}
	return (res);
}

static int	**realloc(int **src, int size, int len)
{
	int		**res;
	int		i;
	int		j;

	if (!(res = (int **)malloc(sizeof(int *) * size * BUFFER_SIZE)))
		error();
	i = -1;
	while (++i < (size - 1) * BUFFER_SIZE)
	{
		if (!(res[i] = (int *)malloc(sizeof(int) * len)))
			error();
		j = -1;
		while (++j < len)
			res[i][j] = src[i][j];
		free(src[i]);
	}
	free(src);
	return (res);
}

int			**reader(char *file_name, t_map *map_info)
{
	int		fd;
	char	*line;
	int		size;
	int		**res;

	if ((fd = read(file_name, O_RDONLY) == -1))
		error();
	if(get_next_line(fd, &line))
		map_info->depth = 1;
	else
		return (NULL);
	map_info->width = get_width(line);
	size = 1;
	if (!(res = (char **)malloc(sizeof(char *) * size * BUFFER_SIZE)))
		error();
	res[0] = get_alts(linei, map_info->width);
	free(line);
	i = 1;
	while (get_next_line(fd, &line))
	{
		map_info->depth++;
		if (map_info->depth > size * BUFFER_SIZE)
			res = realloc(res, ++size, map_info->width);
		res[map_info->depth - 1] = get_alts(line, map_info->width);
		free(line);
	}
	close(fd);
	return (res);
}
