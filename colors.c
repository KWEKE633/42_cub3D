/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:02:24 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/18 07:47:23 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_valid_rgb(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

int	set_color(t_color *target, const char *line)
{
	char	**rgb;

	int r, g, b;
	while (*line == ' ')
		line++;
	rgb = ft_split(line, ',');
	if (!rgb || count_strs(rgb) != 3)
		return (ft_printf("Error\nRGB is invalid: %s\n", line), 1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_strs(rgb);
	if (!is_valid_rgb(r, g, b))
		return (ft_printf("Error\nRGB値が範囲外です: %s\n", line), 1);
	target->r = r;
	target->g = g;
	target->b = b;
	return (0);
}
