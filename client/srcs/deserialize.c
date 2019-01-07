/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 15:10:03 by aabelque          #+#    #+#             */
/*   Updated: 2018/12/21 18:12:33 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void			deserialize_obj(char *data, t_object *obj)
{
	t_object	*otmp;

	otmp = (t_object *)data;
	*obj = *otmp;
	printf("id : %d, diffuse : %.3f, reflect : %.3f, color : %u\n", otmp->id, otmp->diffuse, otmp->reflection, otmp->color.r);
}
