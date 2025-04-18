/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:28:45 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/15 16:14:54 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int get_pixel_color(t_img *texture, int x, int y)
// {
//     int *pixel;

//     pixel = (int *)(texture->addr + (y * texture->line_length + x * (texture->bpp / 8)));
//     return (*pixel);
// }

// void draw_textured_wall(t_complete *game, int x, t_ray *r, int draw_start, int draw_end)
// {
//     int y;
//     int color;
//     int texture_x;
//     int texture_y;
//     int tex_height;
//     int tex_width;
//     t_img *texture;

//     tex_height = 64;
//     tex_width = 64;

//     if (r->side == 0)
//         texture = (r->ray_dir_x > 0) ? game->ea_tex : game->we_tex;
//     else
//         texture = (r->ray_dir_y > 0) ? game->so_tex : game->no_tex;
//     texture_x = (int)(r->wall_x * tex_width);
//     if (r->side == 0 && r->ray_dir_x > 0) 
//         texture_x = tex_width - texture_x - 1;
//     if (r->side == 1 && r->ray_dir_y < 0)
//         texture_x = tex_width - texture_x - 1;

//     y = draw_start;
//     while (y < draw_end)
//     {
//         texture_y = (int)((y - draw_start) * tex_height / (draw_end - draw_start));
//         color = get_pixel_color(texture, texture_x, texture_y);
//         my_mlx_pixel_put(&game->img, x, y, color);
//         y++;
//     }
// }

// void	raycast(t_complete *game)
// {
// 	int		x;
// 	t_ray	r;

// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		double camera_x = 2 * x / (double)WIDTH - 1;
// 		r.ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
// 		r.ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;

// 		r.map_x = (int)game->player.x;
// 		r.map_y = (int)game->player.y;

// 		r.delta_dist_x = (r.ray_dir_x == 0) ? 1e30 : fabs(1 / r.ray_dir_x);
// 		r.delta_dist_y = (r.ray_dir_y == 0) ? 1e30 : fabs(1 / r.ray_dir_y);

// 		if (r.ray_dir_x < 0)
// 		{
// 			r.step_x = -1;
// 			r.side_dist_x = (game->player.x - r.map_x) * r.delta_dist_x;
// 		}
// 		else
// 		{
// 			r.step_x = 1;
// 			r.side_dist_x = (r.map_x + 1.0 - game->player.x) * r.delta_dist_x;
// 		}
// 		if (r.ray_dir_y < 0)
// 		{
// 			r.step_y = -1;
// 			r.side_dist_y = (game->player.y - r.map_y) * r.delta_dist_y;
// 		}
// 		else
// 		{
// 			r.step_y = 1;
// 			r.side_dist_y = (r.map_y + 1.0 - game->player.y) * r.delta_dist_y;
// 		}

// 		int hit = 0;
// 		while (!hit)
// 		{
// 			if (r.side_dist_x < r.side_dist_y)
// 			{
// 				r.side_dist_x += r.delta_dist_x;
// 				r.map_x += r.step_x;
// 				r.side = 0;
// 			}
// 			else
// 			{
// 				r.side_dist_y += r.delta_dist_y;
// 				r.map_y += r.step_y;
// 				r.side = 1;
// 			}
// 			if (game->map[r.map_y][r.map_x] == '1')
// 				hit = 1;
// 		}

// 		if (r.side == 0)
// 			r.perp_wall_dist = (r.map_x - game->player.x + (1 - r.step_x) / 2) / r.ray_dir_x;
// 		else
// 			r.perp_wall_dist = (r.map_y - game->player.y + (1 - r.step_y) / 2) / r.ray_dir_y;

// 		int line_height = (int)(HEIGHT / r.perp_wall_dist);
// 		int draw_start = -line_height / 2 + HEIGHT / 2;
// 		if (draw_start < 0)
// 			draw_start = 0;
// 		int draw_end = line_height / 2 + HEIGHT / 2;
// 		if (draw_end >= HEIGHT)
// 			draw_end = HEIGHT - 1;

// 		draw_textured_wall(game, x, &r, draw_start, draw_end);
// 		x++;
// 	}
// }
