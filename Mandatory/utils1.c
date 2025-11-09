/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:44:08 by achat             #+#    #+#             */
/*   Updated: 2025/11/09 23:44:18 by achat            ###   ########.fr       */
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
