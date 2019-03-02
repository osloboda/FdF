/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 22:49:17 by osloboda          #+#    #+#             */
/*   Updated: 2019/02/09 22:49:22 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	iso(int *x, int *y, int z)
{
	int		previous_x;
	int		previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

void		drawline(t_map *map, int deltax, int deltay, int error)
{
	int		signx;
	int		signy;
	int		error2;

	signx = map->x1 < map->x2 ? 1 : -1;
	signy = map->y1 < map->y2 ? 1 : -1;
	error = deltax - deltay;
	mlx_pixel_put(map->mlx_ptr, map->win_ptr, map->x2 +
			map->x_pad, map->y2 + map->y_pad, map->col);
	while (map->x1 != map->x2 || map->y1 != map->y2)
	{
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, map->x1 +
				map->x_pad, map->y1 + map->y_pad, map->col);
		error2 = error * 2;
		if (error2 > -deltay)
		{
			error -= deltay;
			map->x1 += signx;
		}
		if (error2 < deltax)
		{
			error += deltax;
			map->y1 += signy;
		}
	}
}

void		render3d_x(t_map *map, int x, int y, int j)
{
	int		col_next;

	if (map->col_switch && ft_strchr(map->map[y][x], ','))
		read_color(ft_strchr(map->map[y][x], ',') + 1, &map->col);
	else if (map->col_switch)
		map->col = 0xFFFFFF;
	if (map->col_switch && x + 1 < map->x_s &&
			ft_strchr(map->map[y][x + 1], ','))
		read_color(ft_strchr(map->map[y][x + 1], ',') + 1, &col_next);
	else if (map->col_switch)
		col_next = 0xFFFFFF;
	if (map->col_switch && map->col != col_next)
		map->col = 0xFFFFFF;
	map->x2 = map->k * (x + 1);
	map->y2 = map->k * y;
	map->x1 = map->k * x;
	map->y1 = map->y2;
	iso(&map->x1, &map->y1, j * map->high);
	iso(&map->x2, &map->y2, ft_atoi(map->map[y][x + 1]) * map->high);
	drawline(map, abs(map->x2 - map->x1), abs(map->y2 - map->y1), 0);
}

void		render3d_y(t_map *map, int x, int y, int j)
{
	int		col_next;

	if (map->col_switch && ft_strchr(map->map[y][x], ','))
		read_color(ft_strchr(map->map[y][x], ',') + 1, &map->col);
	else if (map->col_switch)
		map->col = 0xFFFFFF;
	if (map->col_switch && y + 1 < map->y_s &&
			ft_strchr(map->map[y + 1][x], ','))
		read_color(ft_strchr(map->map[y + 1][x], ',') + 1, &col_next);
	else if (map->col_switch)
		col_next = 0xFFFFFF;
	if (map->col_switch && map->col != col_next && map->col != 0xFFFFFF)
		map->col = col_next;
	map->x2 = map->k * x;
	map->y2 = map->k * (y + 1);
	map->x1 = map->x2;
	map->y1 = map->k * y;
	iso(&map->x1, &map->y1, j * map->high);
	iso(&map->x2, &map->y2, ft_atoi(map->map[y + 1][x]) * map->high);
	drawline(map, abs(map->x2 - map->x1), abs(map->y2 - map->y1), 0);
}

void		print3d_img(t_map *map)
{
	int		x;
	int		y;
	int		j;

	y = 0;
	mlx_clear_window(map->mlx_ptr, map->win_ptr);
	while (y < map->y_s)
	{
		x = 0;
		while (x < map->x_s)
		{
			j = ft_atoi(map->map[y][x]);
			if (x + 1 < map->x_s)
				render3d_x(map, x, y, j);
			if (y + 1 < map->y_s)
				render3d_y(map, x, y, j);
			x++;
		}
		y++;
	}
}
