/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:05:43 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/15 15:02:14 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	move_forward(t_complete *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
	if (game->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
	return (1);
}

int	move_backward(t_complete *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (game->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
	return (1);
}

int	move_left(t_complete *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y - game->player.plane_y * MOVE_SPEED;
	if (game->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
	return (1);
}

int	move_right(t_complete *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y + game->player.plane_y * MOVE_SPEED;
	if (game->map[(int)new_y][(int)game->player.x] != '1')
		game->player.y = new_y;
	if (game->map[(int)game->player.y][(int)new_x] != '1')
		game->player.x = new_x;
	return (1);
}
