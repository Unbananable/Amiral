/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filelinecount.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:18:47 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/22 17:57:56 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <unistd.h>

int		ft_filelinecount(int fd)
{
	int		nblines;
	int		readchar;
	char	buf[51];
	int		i;

	nblines = 0;
	while ((readchar = read(fd, buf, 50)) > 0)
	{
		buf[readchar] = 0;
		i = 0;
		while (i < readchar)
		{
			if (buf[i] == '\n')
				nblines++;
			i++;
		}
	}
	return (nblines);
}
