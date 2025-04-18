/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 10:22:22 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/18 11:58:17 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_minimap(t_complete *game)
{
	int	x;
	int	y;
	int	screen_x;
	int	screen_y;
	int	color;
	int	dx;
	int	dy;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			screen_x = x * TILE_SIZE;
			screen_y = y * TILE_SIZE;
			if (game->map[y][x] == '1')
				color = 0x000000;
			else
				color = 0xFFD700;
			dy = 0;
			while (dy < TILE_SIZE)
			{
				dx = 0;
				while (dx < TILE_SIZE)
				{
					my_mlx_pixel_put(&game->img, screen_x + dx, screen_y + dy,
						color);
					dx++;
				}
				dy++;
			}
			x++;
		}
		y++;
	}
}

void	draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1)
	{
		my_mlx_pixel_put(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_minimap_player(t_complete *game)
{
	int		px;
	int		py;
	double	dir_x;
	double	dir_y;
	double	len;
	double	base;
	double	norm_x;
	double	norm_y;
	int		p1x;
	int		p1y;
	int		p2x;
	int		p2y;
	int		p3x;
	int		p3y;

	px = game->player.x * TILE_SIZE;
	py = game->player.y * TILE_SIZE;
	dir_x = game->player.dir_x;
	dir_y = game->player.dir_y;
	len = 10.0;
	base = 5.0;
	p1x = px + (int)(dir_x * len);
	p1y = py + (int)(dir_y * len);
	norm_x = -dir_y;
	norm_y = dir_x;
	p2x = px + (int)(norm_x * base);
	p2y = py + (int)(norm_y * base);
	p3x = px - (int)(norm_x * base);
	p3y = py - (int)(norm_y * base);
	draw_line(&game->img, p1x, p1y, p2x, p2y, 0xFF0000);
	draw_line(&game->img, p1x, p1y, p3x, p3y, 0xFF0000);
	draw_line(&game->img, p2x, p2y, p3x, p3y, 0xFF0000);
}
