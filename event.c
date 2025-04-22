/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:42 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/18 07:48:01 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	controls_working(int command, t_complete *game)
{
	int	works;

	works = 0;
	if (command == 65307)
		exit_point(game);
	if (command == 119)
		works = move_forward(game);
	if (command == 115)
		works = move_backward(game);
	if (command == 97)
		works = move_left(game);
	if (command == 100)
		works = move_right(game);
	if (command == 65361)
		works = rotate_left(game);
	if (command == 65363)
		works = rotate_right(game);
	if (works)
		render_frame(game);
	return (1);
}
