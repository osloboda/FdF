/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 22:49:10 by osloboda          #+#    #+#             */
/*   Updated: 2019/02/09 22:49:13 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		render2d_y(t_map *map, int x, int y)
{
	int		i;
	int		col_next;

	i = 0;
	if (map->col_switch && ft_strchr(map->map[y][x], ','))
		read_color(ft_strchr(map->map[y][x], ',') + 1, &map->col);
	else if (map->col_switch)
		map->col = 0xFFFFFF;
	if (map->col_switch && y + 1 < map->y_s &&
			ft_strchr(map->map[y + 1][x], ','))
		read_color(ft_strchr(map->map[y + 1][x], ',') + 1, &col_next);
	else if (map->col_switch)
		col_next = 0xFFFFFF;
	if (map->col_switch && map->col != col_next)
		map->col = 0xFFFFFF;
	while (map->k * y + ++i < map->k * (y + 1) && y + 1 < map->y_s)
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, map->k * x +
				map->x_pad, map->k * y + i + map->y_pad, map->col);
}

void		render2d_x(t_map *map, int x, int y)
{
	int		i;
	int		col_next;

	i = 0;
	if (map->col_switch && ft_strchr(map->map[y][x], ','))
		read_color(ft_strchr(map->map[y][x], ',') + 1, &map->col);
	else if (map->col_switch)
		map->col = 0xFFFFFF;
	mlx_pixel_put(map->mlx_ptr, map->win_ptr, map->k * x +
			map->x_pad, map->k * y + map->y_pad, map->col);
	if (map->col_switch && x + 1 < map->x_s &&
			ft_strchr(map->map[y][x + 1], ','))
		read_color(ft_strchr(map->map[y][x + 1], ',') + 1, &col_next);
	else if (map->col_switch)
		col_next = 0xFFFFFF;
	if (map->col_switch && map->col != col_next)
		map->col = 0xFFFFFF;
	while (map->k * x + ++i < map->k * (x + 1) && x + 1 < map->x_s)
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, map->k *
				x + i + map->x_pad, map->k * y + map->y_pad, map->col);
	render2d_y(map, x, y);
}

void		print2d_img(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	while (y < map->y_s)
	{
		x = 0;
		while (x < map->x_s)
			render2d_x(map, x++, y);
		y++;
	}
}
