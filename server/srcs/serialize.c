/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 15:09:45 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/21 10:14:52 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			serialize_obj(t_object *obj, char *data)
{
	t_object	*otmp;

	otmp = (t_object *)data;
	*otmp = *obj;
	otmp++;
}
