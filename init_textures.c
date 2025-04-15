/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:09:25 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/15 15:13:38 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	load_textures(t_complete *game)
{
	int w, h;
	game->no_tex = mlx_xpm_file_to_image(game->mlxpointer, "textures/no.xpm", &w, &h);
	game->so_tex = mlx_xpm_file_to_image(game->mlxpointer, "textures/so.xpm", &w, &h);
	game->we_tex = mlx_xpm_file_to_image(game->mlxpointer, "textures/we.xpm", &w, &h);
	game->ea_tex = mlx_xpm_file_to_image(game->mlxpointer, "textures/ea.xpm", &w, &h);
}
