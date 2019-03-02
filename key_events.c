/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 22:48:18 by osloboda          #+#    #+#             */
/*   Updated: 2019/02/10 02:06:07 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		printtips(void)
{
	ft_putstr("Use scroll for zoom\nPress and move mouse for map"
			" moving\n[v] - for switch projection\n[+][-] - for change"
			" height\n[1] - for original colour\n[2] - for PURPLE colour\n"
			"[3] - for RED colour\n[4] - for GREEN colour\n"
			"[3] - for RED colour\n"
			"[5] - for AQUA colour\n[6] - for YELLOW colour\n"
			"[7] - for BLUE colour\n[esc] - for quit\n");
}

void		read_color(char *str, int *res)
{
	int		base;
	int		num;

	base = 16;
	*res = 0;
	while (*str == ' ')
		str++;
	if (*str)
	{
		if (*str++ == '0')
			if (*str == 'x')
				str++;
		while (*str)
		{
			num = ft_toupper(*str++);
			num = (num >= 'A') ? num - 'A' + 0x0a : num - '0';
			if (num >= 0 && num < base)
				*res = *res * base + num;
			else
				break ;
		}
	}
}

void		get_color(int key, t_map *map)
{
	if (key == 18)
		map->col_switch = 1;
	else if (key == 19 && !(map->col_switch = 0))
		map->col = 0x800080;
	else if (key == 20 && !(map->col_switch = 0))
		map->col = 0xFF0000;
	else if (key == 21 && !(map->col_switch = 0))
		map->col = 0x008000;
	else if (key == 22 && !(map->col_switch = 0))
		map->col = 0xFFFF00;
	else if (key == 23 && !(map->col_switch = 0))
		map->col = 0x00FFFF;
	else if (key == 26 && !(map->col_switch = 0))
		map->col = 0x682B4;
}

void		dop_deal_key(int key, t_map *map)
{
	if (key == 53)
		free_map(map);
	if (key == 27)
		map->high--;
	else if (key == 24)
		map->high++;
	else if (key == 9 && map->iso)
	{
		map->iso = 0;
		map->x_pad = (map->win_x - (map->x_s) * map->k / 1.05) / 2;
		map->y_pad = (map->win_y - (map->y_s) * map->k / 1.1) / 2;
	}
	else if (key == 9 && (map->high = map->k))
	{
		map->iso = 1;
		map->x_pad = (map->win_x - (map->x_s) * (map->k / 2)) / 2;
		map->y_pad = (map->win_y - (map->y_s) * (map->k)) / 2;
	}
	else
		get_color(key, map);
}

int			deal_key(int key, t_map *map)
{
	dop_deal_key(key, map);
	if (map->high)
	{
		if (map->high <= map->k)
			map->high_save = map->k / map->high;
		else
			map->high_save = map->high / map->k;
	}
	if (!map->iso)
		print2d_img(map);
	else
		print3d_img(map);
	return (0);
}
