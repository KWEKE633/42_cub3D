/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:09:25 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/17 05:54:53 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

// void	load_textures(t_complete *game)
// {
// 	int w, h;
// 	game->no_tex = mlx_xpm_file_to_image(game->mlxpointer, "textures/no.xpm",
// &w, &h);
// 	game->so_tex = mlx_xpm_file_to_image(game->mlxpointer, "textures/so.xpm",
// &w, &h);
// 	game->we_tex = mlx_xpm_file_to_image(game->mlxpointer, "textures/we.xpm",
// &w, &h);
// 	game->ea_tex = mlx_xpm_file_to_image(game->mlxpointer, "textures/ea.xpm",
// &w, &h);
// }

// void	load_textures(t_complete *game)
// {
// 	int	w;
// 	int	h;

// 	game->noth = malloc(sizeof(t_texture));
// 	game->soth = malloc(sizeof(t_texture));
// 	game->west = malloc(sizeof(t_texture));
// 	game->east = malloc(sizeof(t_texture));
// 	if (!game->noth || !game->soth || !game->west || !game->east)
// 	{
// 		ft_printf("Error\nFailed to allocate memory for textures\n");
// 		exit(1);
// 	}
// 	game->noth->img = mlx_xpm_file_to_image(game->mlxpointer, "textures/no.xpm",
// 			&w, &h);
// 	if (!game->noth->img)
// 	{
// 		ft_printf("Error\nFailed to load NO texture: %s\n", game->texture_no);
// 		exit(1);
// 	}
// 	game->noth->addr = mlx_get_data_addr(game->noth->img,
// 			&game->noth->bits_per_pixel, &game->noth->line_length,
// 			&game->noth->endian);
// 	game->noth->width = w;
// 	game->noth->height = h;
// 	game->soth->img = mlx_xpm_file_to_image(game->mlxpointer, "textures/so.xpm",
// 			&w, &h);
// 	if (!game->soth->img)
// 	{
// 		ft_printf("Error\nFailed to load SO texture: %s\n", game->texture_so);
// 		exit(1);
// 	}
// 	game->soth->addr = mlx_get_data_addr(game->soth->img,
// 			&game->soth->bits_per_pixel, &game->soth->line_length,
// 			&game->soth->endian);
// 	game->soth->width = w;
// 	game->soth->height = h;
// 	game->west->img = mlx_xpm_file_to_image(game->mlxpointer, "textures/we.xpm",
// 			&w, &h);
// 	if (!game->west->img)
// 	{
// 		ft_printf("Error\nFailed to load WE texture: %s\n", game->texture_we);
// 		exit(1);
// 	}
// 	game->west->addr = mlx_get_data_addr(game->west->img,
// 			&game->west->bits_per_pixel, &game->west->line_length,
// 			&game->west->endian);
// 	game->west->width = w;
// 	game->west->height = h;
// 	game->east->img = mlx_xpm_file_to_image(game->mlxpointer, "textures/ea.xpm",
// 			&w, &h);
// 	if (!game->east->img)
// 	{
// 		ft_printf("Error\nFailed to load EA texture: %s\n", game->texture_ea);
// 		exit(1);
// 	}
// 	game->east->addr = mlx_get_data_addr(game->east->img,
// 			&game->east->bits_per_pixel, &game->east->line_length,
// 			&game->east->endian);
// 	game->east->width = w;
// 	game->east->height = h;
// }

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
	return (tex);
}

int	init_textures(t_complete *game)
{
	game->noth = load_texture(game->mlxpointer, "textures/no.xpm");
	game->soth = load_texture(game->mlxpointer, "textures/so.xpm");
	game->west = load_texture(game->mlxpointer, "textures/we.xpm");
	game->east = load_texture(game->mlxpointer, "textures/ea.xpm");
	// game->floor_tex = load_texture(game->mlxpointer, "textures/floor.xpm");
	// game->ceiling_tex = load_texture(game->mlxpointer, "textures/ceiling.xpm");
	if (!game->noth || !game->soth || !game->west || !game->east)
	{
		printf("Error: Failed to load textures\n");
		return (1);
	}
	return (0);
}
