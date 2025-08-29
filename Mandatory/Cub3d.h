/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:20:43 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/08/27 15:10:55 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"


typedef struct s_data	t_data;
typedef struct s_player	t_player;
typedef struct s_map	t_map;
# define WIDTH	800
# define HIGHT	800
#define PLAYER_X 80
#define PLAYER_Y 80


struct s_map
{
	int		player_x;
	int		player_y;
	int		player_dir;
	char	*no_path;
	char	*we_path;
	char	*ea_path;
	char	*so_path;
	int		f_rgb[3];
	int		c_rgb[3];
	char	**map;
	int		map_width;
	int		map_hight;
};

struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
};

struct s_data
{
	mlx_image_t	*img;
	t_map		*map;
	mlx_t		*mlx;
};

void	error(char *st);
int	parsing(t_map *map, int fd, t_data *data);
void	init_mlx(t_data *data);
void	temp_render(t_data *data);
void	loop_hook(void *param);

#endif