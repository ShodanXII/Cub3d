/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:09:10 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/11/09 22:32:13 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E');
}

int	valid_place(char **map, int i, int j)
{
	if (!is_valid_char(map[i][j - 1]) || !is_valid_char(map[i][j + 1])
		|| !is_valid_char(map[i - 1][j]) || !is_valid_char(map[i + 1][j]))
		return (1);
	return (0);
}

void	valid_map(char **map, int count)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N'
				|| map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
			{
				if (i == 0 || i == count - 1 || map[i][j - 1] == '\0'
					|| map[i][j + 1] == '\0' || map[i - 1][j] == '\0'
					|| map[i + 1][j] == '\0')
					error("Map not properly enclosed");
				if (valid_place(map, i, j))
					error("Invalid map boundaries");
			}
			j++;
		}
		i++;
	}
}

void	check_map(char **map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				player_count++;
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
				&& map[i][j] != 32 && map[i][j] != '\t' && map[i][j] != '\n')
				error("Invalid character in map");
			j++;
		}
		i++;
	}
	if (player_count != 1)
		error("Map must have exactly one player");
}

void	parse_map(t_map *map, int fd)
{
	int	count;

	count = store_map(map, fd);
	check_map(map->map);
	valid_map(map->map, count);
}

void	header_map(t_data *data, char *line, int count, int *parsed_count)
{
	char	**work;

	work = ft_split(line, count);
	if (strcmp(work[0], "NO") == 0)
		parse_side(data, work, count, parsed_count);
	else if (strcmp(work[0], "SO") == 0)
		parse_side(data, work, count, parsed_count);
	else if (strcmp(work[0], "EA") == 0)
		parse_side(data, work, count, parsed_count);
	else if (strcmp(work[0], "WE") == 0)
		parse_side(data, work, count, parsed_count);
	else if (strcmp(work[0], "F") == 0)
		parse_fc(data, work, count, parsed_count);
	else if (strcmp(work[0], "C") == 0)
		parse_fc(data, work, count, parsed_count);
	else
		error("Invalid identifier");
	free_split(work);
}

static void	skip_whitespace(char **line, int *i)
{
	while ((*line)[*i] == 32 || ((*line)[*i] >= 9 && (*line)[*i] <= 13))
		(*i)++;
}

static int	process_line(t_map *map, t_data *data, char *line,
				int *parsed_count)
{
	int	count;
	int	i;

	count = count_words(line, 32, ',');
	i = 0;
	skip_whitespace(&line, &i);
	if (!line[i] || line[i] == '\n')
		return (0);
	if (*parsed_count != 6)
		header_map(data, line, count, parsed_count);
	return (1);
}

int	parsing(t_map *map, int fd, t_data *data)
{
	char	*line;
	int		parsed_count;

	parsed_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!process_line(map, data, line, &parsed_count))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (parsed_count == 6)
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

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
	init_mlx(data);
	mlx_loop_hook(data->mlx, &loop_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
