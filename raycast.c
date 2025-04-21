/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:28:45 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/21 10:49:59 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_texture	*get_texture_by_side(t_complete *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (game->east);
		else
			return (game->west);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (game->soth);
		else
			return (game->noth);
	}
}

static int	get_tex_x(t_texture *tex, t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(ray->wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_vertical_line(t_complete *game, t_texture *tex, t_ray *ray,
		int x)
{
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;

	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		color = *(int *)(tex->addr + (tex_y * tex->line_length + ray->tex_x
					* (tex->bits_per_pixel / 8)));
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F; // shadow
		my_mlx_pixel_put(&game->img, x, y, color);
		y++;
	}
}

void	draw_textured_wall(t_complete *game, int x, t_ray *ray, int draw_start,
		int draw_end)
{
	t_texture	*tex;

	tex = get_texture_by_side(game, ray);
	ray->tex_x = get_tex_x(tex, ray);
	ray->draw_start = draw_start;
	ray->draw_end = draw_end;
	draw_vertical_line(game, tex, ray, x);
}

static void	init_ray(int x, t_ray *ray, t_player *player)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

static void	set_dda(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_ray *ray, char **map)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calc_perp_and_wall(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
	{
		ray->perp_wall_dist = (ray->map_x - player->x + (1 - ray->step_x) / 2.0)
			/ ray->ray_dir_x;
		ray->wall_x = player->y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		ray->perp_wall_dist = (ray->map_y - player->y + (1 - ray->step_y) / 2.0)
			/ ray->ray_dir_y;
		ray->wall_x = player->x + ray->perp_wall_dist * ray->ray_dir_x;
	}
	ray->wall_x -= floor(ray->wall_x);
}

static void	calc_line(t_ray *ray)
{
	if (ray->perp_wall_dist < 0.7)
		ray->perp_wall_dist = 0.7;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	if (ray->line_height > HEIGHT)
		ray->line_height = HEIGHT;
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	raycast(t_complete *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(x, &ray, &game->player);
		set_dda(&ray, &game->player);
		perform_dda(&ray, game->map);
		calc_perp_and_wall(&ray, &game->player);
		calc_line(&ray);
		draw_textured_wall(game, x, &ray, ray.draw_start, ray.draw_end);
		x++;
	}
}

// int	get_pixel_color(t_texture *texture, int x, int y)
// {
// 	char	*pixel;
// 	int		color;

// 	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
// 		return (0);
// 	pixel = texture->addr + (y * texture->line_length + x
// 			* (texture->bits_per_pixel / 8));
// 	color = *(unsigned int *)pixel;
// 	return (color);
// }

// void	draw_textured_wall(t_complete *game, int x, t_ray *r, int draw_start,
// 		int draw_end)
// {
// 	int			y;
// 	int			color;
// 	int			texture_x;
// 	int			texture_y;
// 	int			tex_height;
// 	int			tex_width;
// 	t_texture	*texture;

// 	tex_height = 64;
// 	tex_width = 64;
// 	if (r->side == 0)
// 		texture = (r->ray_dir_x > 0) ? game->east : game->west;
// 	else
// 		texture = (r->ray_dir_y > 0) ? game->soth : game->noth;
// 	texture_x = (int)(r->wall_x * (double)tex_width);
// 	if (texture_x < 0)
// 		texture_x = 0;
// 	if (texture_x >= tex_width)
// 		texture_x = tex_width - 1;
// 	if (r->side == 0 && r->ray_dir_x > 0)
// 		texture_x = tex_width - texture_x - 1;
// 	if (r->side == 1 && r->ray_dir_y < 0)
// 		texture_x = tex_width - texture_x - 1;
// 	y = draw_start;
// 	while (y < draw_end)
// 	{
// 		texture_y = (int)((y - draw_start) * tex_height / (draw_end
// 					- draw_start));
// 		if (texture_y < 0)
// 			texture_y = 0;
// 		if (texture_y >= tex_height)
// 			texture_y = tex_height - 1;
// 		color = get_pixel_color(texture, texture_x, texture_y);
// 		my_mlx_pixel_put(&game->img, x, y, color);
// 		y++;
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
