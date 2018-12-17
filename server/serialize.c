/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 15:09:45 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/17 12:53:44 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static	void	serialize_uchar(t_object *obj, unsigned char *data)
{
	*data = obj->color.r;
	data++;
	*data = obj->color.g;
	data++;
	*data = obj->color.b;
	data++;
	*data = obj->color.a;
}

static	void	serialize_int(t_object *obj, int *data)
{
	*data = obj->id;
	data++;
	*data = obj->index;
	data++;
	*data = obj->intersect;
	data++;
	*data = obj->finite;
	data++;
	*data = obj->covered;
	data++;
	*data = obj->has_density;
	data++;
}

void			serialize_obj(t_object *obj, char *data)
{
	int				*itmp;
	float			*ftmp;
	unsigned char	*utmp;

	itmp = (int *)data;
	serialize_int(obj, itmp);
	ftmp = (float *)itmp;
	serialize_float(obj, ftmp);
	utmp = (unsigned char *)ftmp;
	serialize_uchar(obj, utmp);
}
