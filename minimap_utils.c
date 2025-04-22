/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:04:27 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/22 13:05:07 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_abs1(t_minimap *m)
{
	m->dx = abs(m->p2x - m->p1x);
	m->dy = abs(m->p2y - m->p1y);
	m->sx = -1;
	m->sy = -1;
}

void	draw_abs2(t_minimap *m)
{
	m->dx = abs(m->p3x - m->p1x);
	m->dy = abs(m->p3y - m->p1y);
	m->sx = -1;
	m->sy = -1;
}

void	draw_abs3(t_minimap *m)
{
	m->dx = abs(m->p3x - m->p2x);
	m->dy = abs(m->p3y - m->p2y);
	m->sx = -1;
	m->sy = -1;
}
