/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 22:42:27 by achat             #+#    #+#             */
/*   Updated: 2025/11/09 23:55:22 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line || !line[i])
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && 
				line[i] != '\n' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || 
			line[i] == 'N' || line[i] == 'S' || 
			line[i] == 'E' || line[i] == 'W')
			return (1);
		i++;
	}
	return (0);
}

static void	check_map_continuity(char **map)
{
	int	i;
	int	map_started;
	int	map_ended;

	i = 0;
	map_started = 0;
	map_ended = 0;
	while (map[i])
	{
		if (is_map_line(map[i]))
		{
			if (map_ended)
				error("Invalid map: empty line within map");
			map_started = 1;
		}
		else if (map_started && is_empty_line(map[i]))
		{
			map_ended = 1;
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
	check_map_continuity(map);
}

void	parse_map(t_map *map, int fd)
{
	int	count;

	count = store_map(map, fd);
	check_map(map->map);
	valid_map(map->map, count);
}
