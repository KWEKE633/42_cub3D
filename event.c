/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:15:42 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/14 15:46:37 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	controls_working(int command, t_complete *game)
{
	// int	works;

	// works = 0;
	if (command == 65307)
		exit_point(game);
	// if (command == 119)
	// 	works = keyboard_w_s(game, command);
	// if (command == 115)
	// 	works = keyboard_w_s(game, command);
	// if (command == 97)
	// 	works = keyboard_a_d(game, command);
	// if (command == 100)
	// 	works = keyboard_a_d(game, command);
	// if (works)
	// 	adding_in_graphics(game);
	return (1);
}
