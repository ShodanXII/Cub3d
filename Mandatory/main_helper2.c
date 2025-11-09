/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 22:08:12 by achat             #+#    #+#             */
/*   Updated: 2025/11/09 22:35:11 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

t_map	*init_data_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		error("Memory allocation failed");
	ft_memset(map, 0, sizeof(t_map));
	return (map);
}

int	count_words(char const *str, char c, char a)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c || str[i] == a)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c && str[i] != a)
				i++;
		}
	}
	return (count);
}

void	parse_side(t_data *data, char **work, int count, int *parsed_count)
{
	int	len;

	(*parsed_count)++;
	if (count != 2)
		error("Invalid texture arguments");
	len = ft_strlen(work[1]);
	if (len < 5 || strcmp(work[1] + len - 5, ".png\n"))
		error("Texture must be .png format");
	add_data(data, work[0], work[1]);
}

void	parse_fc(t_data *data, char **values, int count, int *parsed_count)
{
	(*parsed_count)++;
	if (count != 4)
		error("Invalid color arguments");
	add_color(data, values);
}
