/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 06:45:51 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/17 07:06:39 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	rotate_left(t_complete *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(-ROTATE_SPEED)
		- game->player.dir_y * sin(-ROTATE_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROTATE_SPEED) + game->player.dir_y
		* cos(-ROTATE_SPEED);
	game->player.plane_x = game->player.plane_x * cos(-ROTATE_SPEED)
		- game->player.plane_y * sin(-ROTATE_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROTATE_SPEED)
		+ game->player.plane_y * cos(-ROTATE_SPEED);
	return (1);
}

int	rotate_right(t_complete *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(ROTATE_SPEED)
		- game->player.dir_y * sin(ROTATE_SPEED);
	game->player.dir_y = old_dir_x * sin(ROTATE_SPEED) + game->player.dir_y
		* cos(ROTATE_SPEED);
	game->player.plane_x = game->player.plane_x * cos(ROTATE_SPEED)
		- game->player.plane_y * sin(ROTATE_SPEED);
	game->player.plane_y = old_plane_x * sin(ROTATE_SPEED)
		+ game->player.plane_y * cos(ROTATE_SPEED);
	return (1);
}
