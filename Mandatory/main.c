/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:09:10 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/11/09 23:17:07 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include <stdlib.h>

static void	set_player_rotation(t_player *player, char c)
{
	if (c == 'S')
		player->rot_angle = PI / 2;
	else if (c == 'N')
		player->rot_angle = 3 * PI / 2;
	else if (c == 'E')
		player->rot_angle = 0;
	else if (c == 'W')
		player->rot_angle = PI;
}

void	init_player(t_data *data)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			c = data->map->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				data->player->pos_x = x + 0.5;
				data->player->pos_y = y + 0.5;
				set_player_rotation(data->player, c);
				data->map->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
	error("No player found in map");
}

static void	validate_args(int ac, char **av, int *fd)
{
	int	len;

	if (ac != 2)
		error("Usage: ./cub3d <map.cub>");
	len = ft_strlen(av[1]);
	*fd = open(av[1], O_RDONLY);
	if (len < 4 || strcmp(av[1] + len - 4, ".cub") || *fd == -1)
		error("Invalid file format or file not found");
}

static t_data	*init_game_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		error("Memory allocation failed");
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		error("Memory allocation failed");
	return (data);
}

void ll()
{
	system("leaks -q cub3d");
}

int	main(int ac, char **av)
{
	t_map	*map;
	t_data	*data;
	int		fd;

	data = init_game_data();
	validate_args(ac, av, &fd);
	map = init_data_map();
	data->map = map;
	if (parsing(map, fd, data))
		parse_map(map, fd);
	init_player(data);
	init_player_direction(data);
	data->textures = init_textures();
	load_textures(data);
	ll();
	init_mlx(data);
	mlx_loop_hook(data->mlx, &loop_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
