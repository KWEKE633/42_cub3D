/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:12:37 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/18 07:55:00 by enkwak           ###   ########.fr       */
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

# define WIDTH 800
# define HEIGHT 600
# define MOVE_SPEED 0.4
# define ROTATE_SPEED 0.2

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

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
	// t_texture	*floor_tex;
	// t_texture	*ceiling_tex;
	t_img		img;
	t_color		floor;
	t_color		ceiling;
}				t_complete;

int				controls_working(int command, t_complete *game);
int				close_window(t_complete *game);
int				exit_point(t_complete *game);
void			if_walls(t_complete *game);
void			character_valid(t_complete *game);
void			check_errors(t_complete *game);
// int				is_map_line(char *line);
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

#endif
