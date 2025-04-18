/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:10:04 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/18 11:06:11 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_floor_ceiling(t_complete *game)
{
	int	color;
	int	x;
	int	y;

	color = (game->ceiling.r << 16) | (game->ceiling.g << 8) | game->ceiling.b;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}
	color = (game->floor.r << 16) | (game->floor.g << 8) | game->floor.b;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	clear_image(t_complete *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlxpointer, game->img.img);
	game->img.img = mlx_new_image(game->mlxpointer, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_length, &game->img.endian);
}

int	render_frame(t_complete *game)
{
	clear_image(game);
	draw_floor_ceiling(game);
	raycast(game);
	draw_minimap(game);
	draw_minimap_player(game);
	mlx_put_image_to_window(game->mlxpointer, game->winpointer, game->img.img,
		0, 0);
	return (0);
}
