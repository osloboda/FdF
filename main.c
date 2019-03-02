/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 13:48:33 by osloboda          #+#    #+#             */
/*   Updated: 2019/02/10 00:08:52 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "printf.h"

void		free_map(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->y_s)
	{
		x = 0;
		while (x < (map->x_s))
			free(map->map[y][x++]);
		free(map->map[y++]);
	}
	free(map->map);
	free(map);
	exit(0);
}

void		rrad(char *str, t_map *map, int x)
{
	int		fd;
	char	*line;
	char	***mass;
	int		i;

	if (1 > (fd = open(str, O_RDONLY)))
	{
		write(1, "No such file.\n", 14);
		free(map);
		exit(0);
	}
	get_next_line(fd, &line);
	x = find(line, ' ');
	free(line);
	i = count_y(fd, 1, x);
	mass = (char***)malloc((i + 1) * sizeof(char **));
	map->map = mass;
	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		*mass++ = ft_strsplit(line, ' ');
		free(line);
	}
	*mass = NULL;
}

void		koef(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	map->x_s = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
			x++;
		if (x > map->x_s)
			map->x_s = x;
		y++;
	}
	map->y_s = y;
	if (map->x_s > map->y_s)
		map->k = map->win_x / map->x_s;
	else
		map->k = map->win_y / map->y_s;
	map->x_pad = (map->win_x - map->x_s * map->k) * 10;
	map->y_pad = (map->win_y - map->y_s * map->k);
}

void		start_rend(char **argv)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->win_x = 800;
	map->win_y = 500;
	map->col_switch = 1;
	if (argv[2] && ft_atoi(argv[2]) > 0 && ft_atoi(argv[2]) < 2561)
		map->win_x = ft_atoi(argv[2]);
	if (argv[3] && ft_atoi(argv[3]) > 0 && ft_atoi(argv[3]) < 1601)
		map->win_y = ft_atoi(argv[3]);
	rrad(argv[1], map, 0);
	koef(map);
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr,
			map->win_x, map->win_y, argv[0]);
	print2d_img(map);
	map->iso = 0;
	map->high = map->k;
	mlx_key_hook(map->win_ptr, deal_key, map);
	mlx_mouse_hook(map->win_ptr, deal_mouse, map);
	mlx_hook(map->win_ptr, 5, INT_MAX, relese_mouse, map);
	mlx_hook(map->win_ptr, 6, INT_MAX, mouse_move, map);
	mlx_loop(map->mlx_ptr);
	free_map(map);
}

int			main(int argc, char **argv)
{
	if (argc > 1 && argc < 5 && argv[1][ft_strlen(argv[1]) - 1] == 'f'
	&& argv[1][ft_strlen(argv[1]) - 2] == 'd' &&
	argv[1][ft_strlen(argv[1]) - 3] == 'f' &&
	argv[1][ft_strlen(argv[1]) - 4] == '.')
	{
		start_rend(argv);
	}
	else
		write(1, "usage: fdf source_file.fdf "
				"x_size_of_window y_size_of_window\n", 61);
	return (0);
}
