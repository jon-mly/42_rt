/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 15:10:03 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/17 17:24:21 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static	void	deserialize_uchar(unsigned char *data, t_object *obj)
{
	obj->color.r = *data;
	data++;
	obj->color.g = *data;
	data++;
	obj->color.b = *data;
	data++;
	obj->color.a = *data;
}

static	void	deserialize_int(int *data, t_object *obj)
{
	obj->id = *data;
	data++;
	obj->index = *data;
	data++;
	obj->intersect = *data;
	data++;
	obj->finite = *data;
	data++;
	obj->covered = *data;
	data++;
	obj->has_density = *data;
	data++;
}

void			deserialize_pt(char *data, t_point *obj)
{
	float *ftmp;

	ftmp = (float *)data;
	obj->x = *ftmp;
	ftmp++;
	obj->y = *ftmp;
	ftmp++;
	obj->z = *ftmp;
}

void			deserialize_obj(char *data, t_object *obj)
{
	int				*itmp;
	float			*ftmp;
	unsigned char	*utmp;

	itmp = (int *)data;
	deserialize_int(itmp, obj);
	ftmp = (float *)itmp;
	deserialize_float(ftmp, obj);
	utmp = (unsigned char *)ftmp;
	deserialize_uchar(utmp, obj);
}
