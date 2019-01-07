/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:20:22 by aabelque          #+#    #+#             */
/*   Updated: 2019/01/07 11:37:39 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			line_len(char **line)
{
	int			count;

	count = 0;
	if (!(line) || !(*line))
		return (0);
	while (line[count])
		count++;
	return (count);
}

void		clear_line(char **line)
{
	int			i;

	i = -1;
	if (line)
	{
		while (line[++i])
			ft_memdel((void**)&(line[i]));
		ft_memdel((void**)&(line[i]));
		ft_memdel((void**)&line);
	}
}

void		exit_if_non_ascii(char *c)
{
	if (c && !(ft_isascii(*c)))
		exit_invalid_file();
}

char		**split_new_line(int fd, int chx)
{
	char		**line;
	char		**splited_content;
	int			res;

	splited_content = NULL;
	if (!(line = (char**)malloc(sizeof(char*))))
		return (NULL);
	if ((res = get_next_line(fd, line)) < 0)
		exit_usage();
	if (chx == 1)
		if (res != 0 && (!*line || is_empty(*line) == 1))
			ft_error("Empty line not allowed in XML");
	if (res == 1)
	{
		ft_striter(*line, &(exit_if_non_ascii));
		splited_content = ft_strsplit(*line, ' ');
	}
	ft_memdel((void**)line);
	ft_memdel((void**)(&line));
	return (splited_content);
}

/*
** Is used in opencl_init.c to specify the number of chars to read, thus
** avoiding an overflow.
*/

size_t		file_len(int fd)
{
	char		*buffer;
	size_t		total_length;
	size_t		res;

	total_length = 0;
	if (!(buffer = (char *)malloc(sizeof(char))))
		return (0);
	while ((res = read(fd, buffer, 1)) > 0)
		total_length += res;
	close(fd);
	ft_memdel((void **)&buffer);
	return (total_length);
}
