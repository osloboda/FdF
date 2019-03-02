/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 22:48:43 by osloboda          #+#    #+#             */
/*   Updated: 2019/02/09 22:48:51 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			count_y(int fd, int i, int x)
{
	char	*line;

	while (get_next_line(fd, &line) && ++i)
	{
		if (find(line, ' ') != x)
		{
			write(1, "Invalid map.\n", 13);
			free(line);
			exit(0);
		}
	}
	printtips();
	close(fd);
	return (i);
}

int			mouse_move(int x, int y, t_map *map)
{
	if (map->press)
	{
		map->x_pad -= (map->x_mouse - x);
		map->y_pad -= (map->y_mouse - y);
		map->x_mouse = x;
		map->y_mouse = y;
		if (!map->iso)
			print2d_img(map);
		else
			print3d_img(map);
	}
	return (0);
}

int			relese_mouse(int button, int x, int y, t_map *map)
{
	if (button == 1)
		map->press = 0;
	if (x != map->x_mouse || y != map->y_mouse)
	{
		map->x_pad -= (map->x_mouse - x);
		map->y_pad -= (map->y_mouse - y);
		if (!map->iso)
			print2d_img(map);
		else
			print3d_img(map);
	}
	return (0);
}

void		dop_deal_mouse(int button, t_map *map, int save_k)
{
	if (button == 1)
		map->press = 1;
	if (button == 5)
		map->k++;
	else if (button == 4 && map->k > 2)
		map->k--;
	if (map->high_save && (button == 5 || button == 4))
	{
		if (map->high <= save_k)
			map->high = map->k / map->high_save;
		else
			map->high = map->high_save * map->k;
	}
	if (button == 4 || button == 5)
	{
		map->x_pad = (map->win_x - (map->x_s) * map->k / 1.05) / 2;
		map->y_pad = (map->win_y - (map->y_s) * map->k / 1.1) / 2;
		if (map->iso)
		{
			map->x_pad = (map->win_x - (map->x_s) * (map->k / 2)) / 2;
			map->y_pad = (map->win_y - (map->y_s) * (map->k)) / 2;
		}
	}
}

int			deal_mouse(int button, int x, int y, t_map *map)
{
	dop_deal_mouse(button, map, map->k);
	map->x_mouse = x;
	map->y_mouse = y;
	if (!map->iso)
		print2d_img(map);
	else
		print3d_img(map);
	return (0);
}
