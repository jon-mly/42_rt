/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:05:34 by jmlynarc          #+#    #+#             */
/*   Updated: 2018/04/17 17:05:35 by jmlynarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buffer	*get_buffer(int fd, t_buffer **node)
{
	t_buffer	*current;

	if (!(node))
	{
		if (!(node = (t_buffer **)malloc(sizeof(t_buffer *))))
			return (NULL);
		*node = NULL;
	}
	current = *node;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	if (!(current = (t_buffer *)malloc(sizeof(t_buffer))))
		return (NULL);
	current->fd = fd;
	current->str = ft_strnew(BUFF_SIZE);
	current->next = *node;
	*node = current;
	return (current);
}

int			extend_line(t_buffer *buffer, char **line)
{
	char		*tmp;
	int			index;

	if (ft_strchr(buffer->str, '\n'))
		index = (int)(ft_strchr(buffer->str, '\n') - buffer->str);
	else
		index = BUFF_SIZE;
	buffer->str[index] = '\0';
	tmp = *line;
	*line = ft_strjoin(tmp, buffer->str);
	free(tmp);
	if (index < BUFF_SIZE)
	{
		ft_memmove(buffer->str, buffer->str + index + 1, BUFF_SIZE - index);
		return (1);
	}
	ft_memset(buffer->str, '\0', BUFF_SIZE);
	return (0);
}

int			find_carriage_return(t_buffer *buffer, char **line)
{
	if (ft_strchr(buffer->str, '\n'))
	{
		extend_line(buffer, line);
		return (1);
	}
	extend_line(buffer, line);
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	int				res;
	static t_buffer	*list = NULL;
	t_buffer		*buffer;

	buffer = get_buffer(fd, &list);
	if (!(buffer) || fd < 0 || !(line) || BUFF_SIZE <= 0)
		return (-1);
	*line = ft_strnew(0);
	if (ft_strlen(buffer->str) > 0 && find_carriage_return(buffer, line))
		return (1);
	while ((res = read(fd, buffer->str, BUFF_SIZE)) > 0 &&
			ft_strchr(buffer->str, '\n') == NULL)
		extend_line(buffer, line);
	if (ft_strchr(buffer->str, '\n'))
	{
		extend_line(buffer, line);
		return (1);
	}
	if (res == -1)
		return (-1);
	return (ft_strlen(*line) > 0 ? 1 : 0);
}
