/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 12:37:36 by osloboda          #+#    #+#             */
/*   Updated: 2019/02/09 15:48:58 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "../libft/libft.h"
# include "limits.h"
# include "math.h"
# include <fcntl.h>

typedef struct	s_map
{
	char		***map;
	void		*mlx_ptr;
	void		*win_ptr;
	double		k;
	double		high_save;
	double		high;
	int			y_s;
	int			x_s;
	int			z_s;
	int			y_pad;
	int			x_pad;
	int			x_mouse;
	int			y_mouse;
	int			press;
	int			iso;
	int			x1;
	int			x2;
	int			y1;
	int			y2;
	int			win_x;
	int			win_y;
	int			col;
	int			col_switch;
}				t_map;

int				deal_key(int key, t_map *map);
int				deal_mouse(int button, int x, int y, t_map *map);
int				relese_mouse(int button, int x, int y, t_map *map);
int				mouse_move(int x, int y, t_map *map);
int				count_y(int fd, int i, int x);
void			print3d_img(t_map *map);
void			print2d_img(t_map *map);
void			read_color(char *str, int *res);
void			free_map(t_map *map);
void			printtips(void);

#endif
