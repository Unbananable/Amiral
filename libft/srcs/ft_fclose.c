/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fclose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:14:07 by anleclab          #+#    #+#             */
/*   Updated: 2019/02/07 17:48:51 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int		ft_fclose(t_file *stream)
{
	if (stream)
	{
		if (close(stream->fd) == -1)
			return (-1);
		ft_bzero(stream->buf, 4097);
	}
	free(stream);
	stream = NULL;
	return (0);
}
