/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:28:45 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/19 20:24:06 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_pixel_color(t_texture *texture, int x, int y)
{
	char	*pixel;
	int		color;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	draw_textured_wall(t_complete *game, int x, t_ray *r, int draw_start,
		int draw_end)
{
	int			y;
	int			color;
	int			texture_x;
	int			texture_y;
	int			tex_height;
	int			tex_width;
	t_texture	*texture;

	tex_height = 64;
	tex_width = 64;
	if (r->side == 0)
		texture = (r->ray_dir_x > 0) ? game->east : game->west;
	else
		texture = (r->ray_dir_y > 0) ? game->soth : game->noth;
	texture_x = (int)(r->wall_x * tex_width);
	if (r->side == 0 && r->ray_dir_x > 0)
		texture_x = tex_width - texture_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		texture_x = tex_width - texture_x - 1;
	y = draw_start;
	while (y < draw_end)
	{
		texture_y = (int)((y - draw_start) * tex_height / (draw_end
					- draw_start));
		color = get_pixel_color(texture, texture_x, texture_y);
		my_mlx_pixel_put(&game->img, x, y, color);
		y++;
	}
}


//色々と計算式を現身落ちにしようとしていじったやつ！！

void	raycast(t_complete *game)
{
	int		x;
	t_ray	r;
	double	camera_x;
	int		hit;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	corrected_dist;
	double	ray_len;
	double	dot;
	double	cos_angle;

	const double fov = 60.0 * (M_PI / 180.0);
	x = 0;
	while (x < WIDTH)
	{
		camera_x = tan(fov / 2.0) * (2.0 * x / (double)WIDTH - 1.0);
		r.ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		r.ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
		r.map_x = (int)game->player.x;
		r.map_y = (int)game->player.y;
		r.delta_dist_x = (r.ray_dir_x == 0) ? 1e30 : fabs(1 / r.ray_dir_x);
		r.delta_dist_y = (r.ray_dir_y == 0) ? 1e30 : fabs(1 / r.ray_dir_y);
		if (r.ray_dir_x < 0)
		{
			r.step_x = -1;
			r.side_dist_x = (game->player.x - r.map_x) * r.delta_dist_x;
		}
		else
		{
			r.step_x = 1;
			r.side_dist_x = (r.map_x + 1.0 - game->player.x) * r.delta_dist_x;
		}
		if (r.ray_dir_y < 0)
		{
			r.step_y = -1;
			r.side_dist_y = (game->player.y - r.map_y) * r.delta_dist_y;
		}
		else
		{
			r.step_y = 1;
			r.side_dist_y = (r.map_y + 1.0 - game->player.y) * r.delta_dist_y;
		}
		hit = 0;
		while (!hit)
		{
			if (r.side_dist_x < r.side_dist_y)
			{
				r.side_dist_x += r.delta_dist_x;
				r.map_x += r.step_x;
				r.side = 0;
			}
			else
			{
				r.side_dist_y += r.delta_dist_y;
				r.map_y += r.step_y;
				r.side = 1;
			}
			if (game->map[r.map_y][r.map_x] == '1')
				hit = 1;
		}
		if (r.side == 0)
		{
			r.perp_wall_dist = (r.map_x - game->player.x + (1 - r.step_x) / 2.0)
				/ r.ray_dir_x;
			r.wall_x = game->player.y + r.perp_wall_dist * r.ray_dir_y;
		}
		else
		{
			r.perp_wall_dist = (r.map_y - game->player.y + (1 - r.step_y) / 2.0)
				/ r.ray_dir_y;
			r.wall_x = game->player.x + r.perp_wall_dist * r.ray_dir_x;
		}
		r.wall_x -= floor(r.wall_x);
		ray_len = sqrt(r.ray_dir_x * r.ray_dir_x + r.ray_dir_y * r.ray_dir_y);
		dot = r.ray_dir_x * game->player.dir_x + r.ray_dir_y
			* game->player.dir_y;
		cos_angle = dot / ray_len;
		// corrected_dist = r.perp_wall_dist * cos_angle;
		corrected_dist = r.perp_wall_dist * cos(atan2(r.ray_dir_y, r.ray_dir_x)
				- atan2(game->player.dir_y, game->player.dir_x));
		line_height = (int)(HEIGHT / corrected_dist);
		draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		draw_textured_wall(game, x, &r, draw_start, draw_end);
		x++;
	}
}





//２番めのやつ！！！！最初の魚眼修正！

// void	raycast(t_complete *game)
// {
// 	int		x;
// 	t_ray	r;
// 	double	camera_x;
// 	int		hit;
// 	int		line_height;
// 	int		draw_start;
// 	int		draw_end;
// 	double	corrected_dist;
// 	double	camera_angle;

// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		camera_x = 2 * x / (double)WIDTH - 1;
// 		r.ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
// 		r.ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
// 		r.map_x = (int)game->player.x;
// 		r.map_y = (int)game->player.y;
// 		if (r.ray_dir_x == 0)
// 			r.delta_dist_x = 1e30;
// 		else
// 			r.delta_dist_x = fabs(1 / r.ray_dir_x);
// 		if (r.ray_dir_y == 0)
// 			r.delta_dist_y = 1e30;
// 		else
// 			r.delta_dist_y = fabs(1 / r.ray_dir_y);
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
// 		hit = 0;
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
// 		{
// 			r.perp_wall_dist = (r.map_x - game->player.x + (1 - r.step_x) / 2.0)
// 				/ r.ray_dir_x;
// 			r.wall_x = game->player.y + r.perp_wall_dist * r.ray_dir_y;
// 		}
// 		else
// 		{
// 			r.perp_wall_dist = (r.map_y - game->player.y + (1 - r.step_y) / 2.0)
// 				/ r.ray_dir_y;
// 			r.wall_x = game->player.x + r.perp_wall_dist * r.ray_dir_x;
// 		}
// 		r.wall_x -= floor(r.wall_x);
// 		camera_angle = atan(camera_x);
// 		corrected_dist = r.perp_wall_dist * cos(camera_angle);
// 		line_height = (int)(HEIGHT / corrected_dist);
// 		draw_start = -line_height / 2 + HEIGHT / 2;
// 		if (draw_start < 0)
// 			draw_start = 0;
// 		draw_end = line_height / 2 + HEIGHT / 2;
// 		if (draw_end >= HEIGHT)
// 			draw_end = HEIGHT - 1;
// 		draw_textured_wall(game, x, &r, draw_start, draw_end);
// 		x++;
// 	}
// }





//一番最初のやつ！！

// void	raycast(t_complete *game)
// {
// 	int		x;
// 	t_ray	r;
// 	double	camera_x;
// 	int		hit;
// 	int		line_height;
// 	int		draw_start;
// 	int		draw_end;

// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		camera_x = 2 * x / (double)WIDTH - 1;
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
// 		hit = 0;
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
// 			r.perp_wall_dist = (r.map_x - game->player.x + (1 - r.step_x) / 2)
// 				/ r.ray_dir_x;
// 		else
// 			r.perp_wall_dist = (r.map_y - game->player.y + (1 - r.step_y) / 2)
// 				/ r.ray_dir_y;
// 		if (r.side == 0)
// 			r.wall_x = game->player.y + r.perp_wall_dist * r.ray_dir_y;
// 		else
// 			r.wall_x = game->player.x + r.perp_wall_dist * r.ray_dir_x;
// 		r.wall_x -= floor(r.wall_x);
// 		line_height = (int)(HEIGHT / r.perp_wall_dist);
// 		draw_start = -line_height / 2 + HEIGHT / 2;
// 		if (draw_start < 0)
// 			draw_start = 0;
// 		draw_end = line_height / 2 + HEIGHT / 2;
// 		if (draw_end >= HEIGHT)
// 			draw_end = HEIGHT - 1;
// 		draw_textured_wall(game, x, &r, draw_start, draw_end);
// 		x++;
// 	}
// }
