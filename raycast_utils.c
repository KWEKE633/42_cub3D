/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:06:11 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/22 13:32:00 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_pixel_color(t_texture *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

t_texture	*get_texture_by_side(t_ray *ray, t_complete *game)
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

void	draw_vertical_line(t_ray *ray, t_complete *game, int x)
{
	t_texture	*tex;
	t_rcast		r;

	tex = get_texture_by_side(ray, game);
	r.tex_x = (int)(ray->wall_x * (double)(tex->width));
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		r.tex_x = tex->width - r.tex_x - 1;
	r.step = 1.0 * tex->height / ray->line_height;
	r.tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * r.step;
	r.y = ray->draw_start;
	while (r.y < ray->draw_end)
	{
		r.tex_y = (int)r.tex_pos & (tex->height - 1);
		r.tex_pos += r.step;
		r.color = get_pixel_color(tex, r.tex_x, r.tex_y);
		my_mlx_pixel_put(&game->img, x, r.y, r.color);
		r.y++;
	}
}

void	calc_raydir(t_ray *ray, t_player *player, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}
