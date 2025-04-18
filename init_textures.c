/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:09:25 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/18 11:15:51 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static t_texture	*load_texture(void *mlx, char *path)
{
	t_texture	*tex;

	tex = malloc(sizeof(t_texture));
	if (!tex)
		return (NULL);
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		return (free(tex), NULL);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	if (!tex->addr)
		return (free(tex), NULL);
	return (tex);
}

int	init_textures(t_complete *game)
{
	game->noth = load_texture(game->mlxpointer, "textures/no.xpm");
	game->soth = load_texture(game->mlxpointer, "textures/so.xpm");
	game->west = load_texture(game->mlxpointer, "textures/we.xpm");
	game->east = load_texture(game->mlxpointer, "textures/ea.xpm");
	if (!game->noth || !game->soth || !game->west || !game->east)
	{
		printf("Error: Failed to load textures\n");
		return (1);
	}
	return (0);
}
