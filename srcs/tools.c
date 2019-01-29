/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 13:19:37 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/29 13:27:52 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

t_point	**initialize_proj_map(int width, int depth)
{
	t_point **res;
	int		i;

	if (!(res = (t_point **)malloc(sizeof(t_point *) * depth)))
		return (NULL);
	i = -1;
	while (++i < depth)
		if (!(res[i] = (t_point *)malloc(sizeof(t_point) * width)))
		{
			free_2d_tpoint_tab(&res, i);
			return (NULL);
		}
	return (res);
}
