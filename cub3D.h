/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:12:37 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/22 13:30:44 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./gnl/get_next_line.h"
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include "./printf/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 1800
# define HEIGHT 1600
# define MOVE_SPEED 0.2
# define ROTATE_SPEED 0.25
# define TILE_SIZE 10
# define COLLISION_MARGIN 0.4

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define FOV_DEG 60.0
// # define FOV_RAD (FOV_DEG * M_PI / 180.0)

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_minimap
{
	int			px;
	int			py;
	double		dir_x;
	double		dir_y;
	double		len;
	double		base;
	double		norm_x;
	double		norm_y;
	int			p1x;
	int			p1y;
	int			p2x;
	int			p2y;
	int			p3x;
	int			p3y;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
}				t_minimap;

typedef struct s_mini
{
	int			x;
	int			y;
	int			screen_x;
	int			screen_y;
	int			color;
	int			dx;
	int			dy;
}				t_mini;

typedef struct s_rcast
{
	double		step;
	double		tex_pos;
	int			y;
	int			color;
	int			tex_x;
	int			tex_y;
}				t_rcast;

typedef struct s_char
{
	int			height;
	int			width;
	int			i;
	int			player_x;
	int			player_y;
	char		**map_copy;
}				t_char;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			bpp;
}				t_img;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_texture;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		angle;
}				t_player;

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	double		wall_x;
	int			tex_x;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

typedef struct s_start
{
	int			fd;
	int			heightmap;
	int			*widthmap;
	int			playercount;
	int			x_axis;
	int			y_axis;
	int			counter;
	char		**map;
	void		*floors;
	void		*barrier;
	void		*players;
	void		*mlxpointer;
	void		*winpointer;
	int			floor_color;
	int			ceiling_color;
	char		*no_tex;
	char		*so_tex;
	char		*we_tex;
	char		*ea_tex;
	t_player	player;
	t_texture	*noth;
	t_texture	*soth;
	t_texture	*west;
	t_texture	*east;
	t_img		img;
	t_color		floor;
	t_color		ceiling;
}				t_complete;

int				controls_working(int command, t_complete *game);
int				close_window(t_complete *game);
int				exit_point(t_complete *game);
void			if_walls(t_complete *game);
void			character_valid(t_complete *game);
void			free_strs(char **strs);
int				count_strs(char **strs);
int				parse_identifier(t_complete *game, char *line);
int				parse_cubfile(t_complete *game, char *filename);
int				map_reading(t_complete *game, char *line);
int				set_color(t_color *target, const char *line);
int				ft_strcmp(const char *s1, const char *s2);
void			set_player_dir(t_player *player, char dir);
int				move_forward(t_complete *game);
int				move_backward(t_complete *game);
int				move_left(t_complete *game);
int				move_right(t_complete *game);

void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
int				init_textures(t_complete *game);
int				render_frame(t_complete *game);
void			raycast(t_complete *game);
int				rotate_left(t_complete *game);
int				rotate_right(t_complete *game);

void			draw_minimap(t_complete *game, t_mini min);
void			draw_minimap_player(t_complete *game);
int				is_empty_line(const char *line);
int				map_all_wall(char **map, int height);
void			draw_abs1(t_minimap *m);
void			draw_abs2(t_minimap *m);
void			draw_abs3(t_minimap *m);
int				get_pixel_color(t_texture *tex, int x, int y);
t_texture		*get_texture_by_side(t_ray *ray, t_complete *game);
void			draw_vertical_line(t_ray *ray, t_complete *game, int x);
void			calc_raydir(t_ray *ray, t_player *player, int x);

#endif
