/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 15:59:10 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/01/11 12:51:49 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

static unsigned int	ft_strrlen(char *lock)
{
	unsigned int	i;

	i = 0;
	while (lock[i] != '\n' && lock[i] != '\0')
		i++;
	return (i);
}

static char			*ft_strnjoin(char *s1, char *s2, size_t len)
{
	char	*str;
	int		nb;
	char	*tmp;

	nb = ft_strlen(s1) + len++;
	str = ft_strnew(nb);
	tmp = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2 && --len > 0)
		*str++ = *s2++;
	*str = '\0';
	return (tmp);
}

static char			*ft_chrandcpy(char *lock)
{
	if (ft_strchr(lock, '\n'))
	{
		ft_strcpy(lock, ft_strchr(lock, '\n') + 1);
		return (lock);
	}
	if (ft_strrlen(lock) > 0)
	{
		ft_strcpy(lock, ft_strchr(lock, '\0'));
		return (lock);
	}
	return (NULL);
}

int					get_next_line(int const fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	static char	*lock[1023];
	int			res;
	char		*tmp;

	if (fd < 0 || BUFF_SIZE < 1 || !line || read(fd, buff, 0) < 0)
		return (-1);
	if (!(lock[fd]) && (lock[fd] = ft_strnew(0)) == NULL)
		return (-1);
	while (!(ft_strchr(lock[fd], '\n')) &&
			(res = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[res] = '\0';
		tmp = lock[fd];
		lock[fd] = ft_strnjoin(tmp, buff, res);
		free(tmp);
	}
	*line = ft_strsub(lock[fd], 0, ft_strrlen(lock[fd]));
	if (ft_chrandcpy(lock[fd]) == NULL)
	{
		ft_strdel((&lock[fd]));
		return (0);
	}
	return (1);
}
