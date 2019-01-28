/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fclose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:14:07 by anleclab          #+#    #+#             */
/*   Updated: 2019/01/28 18:38:32 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int		ft_fclose(t_file *stream)
{
	if (!stream)
		return (0);
	if (close(stream->fd) == -1)
		return (-1);
	ft_bzero(stream->buf, 4097);
	return (0);
}
