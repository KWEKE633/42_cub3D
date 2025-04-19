/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:12:26 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/19 15:14:59 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static int	validate_file_extension(const char *filename)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (filename[i])
		i++;
	len = i;
	if (len < 4 || ft_strcmp(&filename[len - 4], ".cub") != 0)
		return (0);
	return (1);
}

int	main_sub(t_complete *game)
{
	if (!game->mlxpointer)
	{
		ft_printf("Error\nFailed to initialize MLX.\n");
		exit_point(game);
		return (1);
	}
	game->winpointer = mlx_new_window(game->mlxpointer, WIDTH, HEIGHT, "cub3D");
	if (!game->winpointer)
	{
		if (game->mlxpointer)
		{
			mlx_destroy_display(game->mlxpointer);
			free(game->mlxpointer);
		}
		ft_printf("Error\nFailed to create a new window.\n");
		exit_point(game);
		return (1);
	}
	if (init_textures(game))
		exit_point(game);
	render_frame(game);
	mlx_key_hook(game->winpointer, controls_working, game);
	mlx_hook(game->winpointer, 17, 0, close_window, game);
	mlx_loop(game->mlxpointer);
	return (0);
}

int	main(int argc, char **argv)
{
	t_complete	game;

	if (argc != 2)
	{
		ft_printf("Error\nfailed argc!\n");
		return (1);
	}
	if (!validate_file_extension(argv[1]))
	{
		ft_printf("Error\nInvalid file extension. Expected .cub\n");
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_complete));
	if (parse_cubfile(&game, argv[1]))
	{
		ft_printf("Error\nFailed to read the map.\n");
		exit_point(&game);
	}
	check_errors(&game);
	game.mlxpointer = mlx_init();
	return (main_sub(&game));
}
