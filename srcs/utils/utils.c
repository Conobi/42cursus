/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:26:16 by abastos           #+#    #+#             */
/*   Updated: 2022/08/16 04:53:34 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

bool	out_of_bounds(t_ctx *c, double x, double y)
{
	return (x < 0 || x >= c->map->width || y < 0 || y >= c->map->height);
}

double	to_radians(int degrees)
{
	return ((degrees * M_PI) / 180);
}
