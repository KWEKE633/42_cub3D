/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:22:22 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/22 13:04:59 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_minimap(t_complete *game, t_mini min)
{
	while (game->map[min.y++])
	{
		min.x = 0;
		while (game->map[min.y -1][min.x])
		{
			min.screen_x = min.x * TILE_SIZE;
			min.screen_y = (min.y - 1) * TILE_SIZE;
			min.color = 0xFFD700;
			if (game->map[min.y - 1][min.x] == '1')
				min.color = 0x000000;
			min.dy = 0;
			while (min.dy < TILE_SIZE)
			{
				min.dx = 0;
				while (min.dx < TILE_SIZE)
				{
					my_mlx_pixel_put(&game->img, min.screen_x + min.dx,
						min.screen_y + min.dy, min.color);
					min.dx++;
				}
				min.dy++;
			}
			min.x++;
		}
	}
}

void	draw_line1(t_img *img, t_minimap m, int color)
{
	draw_abs1(&m);
	if (m.p1x < m.p2x)
		m.sx = 1;
	if (m.p1y < m.p2y)
		m.sy = 1;
	m.err = m.dx - m.dy;
	while (1)
	{
		my_mlx_pixel_put(img, m.p1x, m.p1y, color);
		if (m.p1x == m.p2x && m.p1y == m.p2y)
			break ;
		m.e2 = 2 * m.err;
		if (m.e2 > -m.dy)
		{
			m.err -= m.dy;
			m.p1x += m.sx;
		}
		if (m.e2 < m.dx)
		{
			m.err += m.dx;
			m.p1y += m.sy;
		}
	}
}

void	draw_line2(t_img *img, t_minimap m, int color)
{
	draw_abs2(&m);
	if (m.p1x < m.p3x)
		m.sx = 1;
	if (m.p1y < m.p3y)
		m.sy = 1;
	m.err = m.dx - m.dy;
	while (1)
	{
		my_mlx_pixel_put(img, m.p1x, m.p1y, color);
		if (m.p1x == m.p3x && m.p1y == m.p3y)
			break ;
		m.e2 = 2 * m.err;
		if (m.e2 > -m.dy)
		{
			m.err -= m.dy;
			m.p1x += m.sx;
		}
		if (m.e2 < m.dx)
		{
			m.err += m.dx;
			m.p1y += m.sy;
		}
	}
}

void	draw_line3(t_img *img, t_minimap m, int color)
{
	draw_abs3(&m);
	if (m.p2x < m.p3x)
		m.sx = 1;
	if (m.p2y < m.p3y)
		m.sy = 1;
	m.err = m.dx - m.dy;
	while (1)
	{
		my_mlx_pixel_put(img, m.p2x, m.p2y, color);
		if (m.p2x == m.p3x && m.p2y == m.p3y)
			break ;
		m.e2 = 2 * m.err;
		if (m.e2 > -m.dy)
		{
			m.err -= m.dy;
			m.p2x += m.sx;
		}
		if (m.e2 < m.dx)
		{
			m.err += m.dx;
			m.p2y += m.sy;
		}
	}
}

void	draw_minimap_player(t_complete *game)
{
	t_minimap	mini;

	mini.px = game->player.x * TILE_SIZE;
	mini.py = game->player.y * TILE_SIZE;
	mini.dir_x = game->player.dir_x;
	mini.dir_y = game->player.dir_y;
	mini.len = 10.0;
	mini.base = 5.0;
	mini.p1x = mini.px + (int)(mini.dir_x * mini.len);
	mini.p1y = mini.py + (int)(mini.dir_y * mini.len);
	mini.norm_x = -mini.dir_y;
	mini.norm_y = mini.dir_x;
	mini.p2x = mini.px + (int)(mini.norm_x * mini.base);
	mini.p2y = mini.py + (int)(mini.norm_y * mini.base);
	mini.p3x = mini.px - (int)(mini.norm_x * mini.base);
	mini.p3y = mini.py - (int)(mini.norm_y * mini.base);
	draw_line1(&game->img, mini, 0xFF0000);
	draw_line2(&game->img, mini, 0xFF0000);
	draw_line3(&game->img, mini, 0xFF0000);
}
