/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 15:09:45 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/12 15:43:31 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void serialize_int(t_object *obj, int *data)
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

void		serialize_obj(t_object *obj, char *data)
{
	int		*itmp;
	float	*ftmp;

	itmp = (int *)data;
	serialize_int(obj, itmp);
}

void		serialize_light(t_light *light, char *data)
{
	int		*tmp;
}
