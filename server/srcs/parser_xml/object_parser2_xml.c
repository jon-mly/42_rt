/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parser2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 12:22:41 by aabelque          #+#    #+#             */
/*   Updated: 2019/01/06 15:13:16 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_obj_help_xml(t_object *obj)
{
	if (obj->txt_type == CHECKER || obj->txt_type == HORIZONTAL_CIRCLE
			|| obj->txt_type == VERTICAL_CIRCLE || obj->txt_type == DOTS
			|| obj->txt_type == DOTS_REVERTED || obj->txt_type == DOTS_CROWN
			|| obj->txt_type == DOTS_REVERTED_CROWN)
		obj->txt_algo = PROCEDURAL;
	else if (obj->txt_type == PERLIN || obj->txt_type == WOOD
			|| obj->txt_type == MARBLE)
		obj->txt_algo = PERLIN_ALGO;
	else
		obj->txt_algo = NO_ALGO;
}
